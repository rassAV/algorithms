from enum import Enum
import struct


class Alignment(Enum):
    HORIZONTAL = 1
    VERTICAL = 2


class Widget():
    def __init__(self, parent):
        self.parent = parent
        self.childrens = []

        if self.parent is not None:
            self.parent.add_children(self)

    def getParent(self):
        return self.parent

    def getChildrens(self):
        return self.childrens

    def getAlignment(self):
        return self.alignment
    
    def add_children(self, children: "Widget"):
        self.childrens.append(children)

    def to_binary(self, generation=0, count_brother=0):
        d = {'MainWindow': 0, 'Layout':1, 'LineEdit':2, 'ComboBox':3}
        classname = self.__class__.__name__
        result = "" + str(d[classname])
        
        if classname == 'MainWindow':
            result += self.title
        elif classname == 'Layout':
            result += str(generation)
            result += '/'                
            if str(self.alignment)[10:] == 'HORIZONTAL':
                result += '1'
            else:
                result += '2'
        elif classname == 'LineEdit':
            result += str(generation)
            result += '/'
            result += str(self.max_length)
        elif classname == 'ComboBox':
            result += str(generation)
            result += '/'.join(map(str, self.items))

        if classname != 'MainWindow':
            generation += 1 + count_brother
        result += '//'

        count_childrens = len(self.getChildrens())
        for i in range(count_childrens):
            result += self.getChildrens()[i].to_binary(generation, i)
        
        return result

    @classmethod
    def from_binary(self, data, num=0, result=[], arr_gen = [0]):
        a = data[num]
        classname = a
        b = -1
        
        if classname == '0':
            title = ''
            while a != '/' and data[num+1] != '/':
                num += 1
                a = data[num]
                title += a                
            select = MainWindow(title)
            result.append(select)
        elif classname == '1':
            num += 1
            b = int(data[num])
            num += 2
            alignment = int(data[num])
            select = Layout(result[b], Alignment(alignment))
            position = 1 + arr_gen[b]
            for i in range(b):
                position += arr_gen[i]
            result.insert(position, select)
        elif classname == '2':
            num += 1
            b = int(data[num])
            max_len = ""
            num += 2
            a = data[num]
            while a != '/' and data[num+1] != '/':
                max_len += a
                num += 1
                a = data[num]
                   
            select = LineEdit(result[b], int(max_len))
                
            if len(arr_gen) < b+1:
                arr_gen.append(0)
            position = 1 + arr_gen[b]
            for i in range(b):
                position += arr_gen[i]
            result.insert(position, select)
        elif classname == '3':
            num += 1
            b = int(data[num])
            items = []
            num += 2
            a = data[num]
            while not(a == '/' and data[num-1] == '/'):
                item = ''
                while a != '/':
                    item += a
                    num += 1
                    a = data[num]
                items.append(item)
                num += 1
                a = data[num]
            select = ComboBox(result[b], items)
            if len(arr_gen) < b+1:
                arr_gen.append(0)
            position = 1 + arr_gen[b]
            for i in range(b):
                position += arr_gen[i]
            result.insert(position, select)
            num -= 2
        num += 3

        if len(arr_gen) < b+1:
            arr_gen.append(1)
        elif b >= 0:
            arr_gen[b] += 1
        if num < len(data):
            self.from_binary(data, num, result, arr_gen)
            
        return result[0]

    def __str__(self):
        return f"{self.__class__.__name__}{self.childrens}"

    def __repr__(self):
        return str(self)


class MainWindow(Widget):

    def __init__(self, title: str):
        super().__init__(None)
        self.title = title

class Layout(Widget):

    def __init__(self, parent, alignment: Alignment):
        super().__init__(parent)
        self.alignment = alignment

class LineEdit(Widget):

    def __init__(self, parent, max_length: int=10):
        super().__init__(parent)
        self.max_length = max_length

class ComboBox(Widget):

    def __init__(self, parent, items):
        super().__init__(parent)
        self.items = items



app = MainWindow("Application")
layout1 = Layout(app, Alignment.HORIZONTAL)
layout2 = Layout(app, Alignment.VERTICAL)

edit1 = LineEdit(layout1, 20)
edit2 = LineEdit(layout1, 30)

box1 = ComboBox(layout2, [1, 2, 3, 4])
box2 = ComboBox(layout2, ["a", "b", "c"])



print(app)
s_bin = app.to_binary()

print(s_bin)
print(len(s_bin))

new_app = MainWindow.from_binary(s_bin)
print(new_app)
