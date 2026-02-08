from tkinter import *
from tkinter import filedialog as fd
from tkinter.messagebox import showinfo
from fileManipulator import *
from inputValidator import *

# инициализация главного окна
rootWin = Tk()
rootWin.title('Base Plugin Creator')
rootWin.resizable(False, False)
# для центровки главного окна
w = rootWin.winfo_reqwidth()
h = rootWin.winfo_reqheight()
ws = rootWin.winfo_screenwidth()
hs = rootWin.winfo_screenheight()
x = (ws / 2) - (w / 2)
y = (hs / 2) - (h / 2)
rootWin.geometry('+%d+%d' % (x, y))  
# значение checkBox
chkBoxValue = IntVar()
# главная функция
def create_project():
        if check_if_empty(txtBox1.get()) or check_if_empty(txtBox2.get()) or check_if_empty(txtBox3.get()) or check_if_empty(txtBox4.get()):
               showinfo(title='Ошибка', message='Поля не могут быть пустыми', icon='warning') # чисто info
               return 
        # remove_previuos_files(txtBox3.get() + '/')
        copy_files(txtBox2.get(), txtBox3.get())
        copy_directory(txtBox2.get(), txtBox3.get())
        rename_files(txtBox3.get(), txtBox1.get())
        prepare_file_contents(txtBox3.get() + '/' + txtBox1.get() + '.cpp', txtBox1.get())
        prepare_file_contents(txtBox3.get() + '/' + txtBox1.get() + '.h', txtBox1.get())
        prepare_file_contents(txtBox3.get() + '/' + txtBox1.get() + '.pro', txtBox1.get())
        prepare_file_contents(txtBox3.get() + '/' + txtBox1.get().lower() + '.fobd', txtBox1.get())
        copy_file(txtBox3.get() + '/' + txtBox1.get().lower() + '.fobd', txtBox4.get())
        if chkBoxValue.get() == 1:
                generate_bash(txtBox3.get(), txtBox1.get(), 'tarball', txtBox1.get())
                generate_bash(txtBox3.get(), txtBox1.get(), 'build copying', txtBox1.get())
        showinfo(title='Статус выполнения', message='Готово\t\t\t\t', icon='info') # чисто info
# выбор файла 
def select_file():
        filetypes = (('text files', '*.txt'), ('All files', '*.*'))
        filename = fd.askopenfilename(title='Open a file', initialdir='/', filetypes=filetypes)
        # showinfo(title='Selected File', message=filename) # чисто info
# выбор пути с исходной болванкой Qt
def select_pattern_folder():
        filetypes = (('text files', '*.txt'), ('All files', '*.*'))
        folderName = fd.askdirectory(parent=rootWin, initialdir="/home/user/dev", title='Please select a directory')
        # showinfo(title='Selected folder:', message=folderName) # чисто info
        txtBox2.insert(0, folderName) 
# выбор пути с новым проектом
def select_output_folder():
        filetypes = (('text files', '*.txt'), ('All files', '*.*'))
        folderName = fd.askdirectory(parent=rootWin, initialdir="/home/user",title='Please select a directory')
        # showinfo(title='Selected folder:', message=folderName)  # чисто info
        txtBox3.insert(0, folderName) 
# выбор пути с исходными кодами мат.моделей
def select_models_folder():
        filetypes = (('text files', '*.txt'), ('All files', '*.*'))
        folderName = fd.askdirectory(parent=rootWin, initialdir="/home/user",title='Please select a directory')
        # showinfo(title='Selected folder:', message=folderName)  # чисто info
        txtBox5.insert(0, folderName) 

labelName = Label(rootWin, text='Имя создаваемого проекта:')
labelName.grid(row=0, column=0, sticky="E")
labelName = Label(rootWin, text='Путь к исходному шаблону:')
labelName.grid(row=1, column=0, sticky="E")
labelName = Label(rootWin, text='Выходной путь создаваемого проекта:')
labelName.grid(row=2, column=0)
labelRepository = Label(rootWin, text='Точное имя репозитория:')
labelRepository.grid(row=3, column=0, sticky="E")
labelMathModelPath = Label(rootWin, text='Путь к исходникам мат.моделей:')
labelMathModelPath.grid(row=4, column=0, sticky="E", pady=(20,0))
 
txtBox1 = Entry(rootWin, width=30)
txtBox1.grid(row=0, column=1, pady=(8, 8))
txtBox2 = Entry(rootWin, width=30)
txtBox2.grid(row=1, column=1, pady=(8, 8))
txtBox3 = Entry(rootWin, width=30)
txtBox3.grid(row=2, column=1, pady=(8, 8))
txtBox4 = Entry(rootWin, width=30)
txtBox4.grid(row=3, column=1, pady=(8, 8))
txtBox5 = Entry(rootWin, width=30)
txtBox5.grid(row=4, column=1, pady=(25, 8))

chkButton = Checkbutton(rootWin, text='создать bash-скрипты', onvalue=1, offvalue=0, variable=chkBoxValue)
chkButton.grid(row=3, column=2, pady=(8, 8))
#chkButton.toggle() # поставить в True по умолчанию
# кнопки
button1 = Button(rootWin, text='Выйти', width=15, command=rootWin.destroy)
button1.grid(row=5, column=1, pady=(8, 8))
button2 = Button(rootWin, text='Обзор...', width=10, command=select_pattern_folder)
button2.grid(row=1, column=2, padx=(5, 5))
button3 = Button(rootWin, text='Создать', width=15, command=create_project)
button3.grid(row=5, column=0, pady=(8, 8))
button4 = Button(rootWin, text='Обзор...', width=10, height=1, command=select_output_folder)
button4.grid(row=2, column=2, padx=(5, 5))
button5 = Button(rootWin, text='Обзор...', width=10, height=1, command=select_models_folder)
button5.grid(row=4, column=2, padx=(5, 5), pady=(20,0))
button6 = Button(rootWin, text='Встроить->', width=10, height=1, command=select_models_folder)
button6.grid(row=4, column=3, padx=(5, 5), pady=(20,0))
# главный цикл приложения 
rootWin.mainloop()

