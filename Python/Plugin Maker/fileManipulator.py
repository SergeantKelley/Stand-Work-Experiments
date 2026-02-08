# модуль операций над файлами и каталогами
import shutil, sys, fileinput, os
import tarfile
from tkinter.messagebox import showinfo
from os import walk, rename

def copy_files(dir, destinationPath):
        # copy the contents  
         filenames = next(walk(dir), (None, None, []))[2]  # [] if no file
         for file in filenames:
            shutil.copyfile(dir + '/' + file, destinationPath + '/' + file)

def copy_directory(dir, destinationPath):
        destination = shutil.copytree(dir + '/lib', destinationPath + '/lib')

def copy_file(FobdFile, NameOfRepository):
         arrayOfStrings = FobdFile.split("/")
         destinationPath = '/home/shared/repos/' + NameOfRepository + '/Common/DBDF/'
         for fobd in arrayOfStrings:
            if '.fobd' in fobd:
               shutil.copyfile(FobdFile, destinationPath + '/' + fobd)   

def rename_files(dir, new_file_name):
         filenames = next(walk(dir), (None, None, []))[2]  # [] if no file
         for file in filenames:
             if(file.startswith("NoName")):
                print(file)
                rename(dir + '/' + file, dir + '/'+ file.replace("NoName", new_file_name, 1))    
             if(file.startswith("noname")):
                rename(dir + '/' + file, dir + '/'+ file.replace("noname", new_file_name.lower(), 1))    
# удаление старых файлов при повторном нажатии на создать (чтоб избежать исключения Python)
def remove_previuos_files(dir):
            try:
               with os.scandir(dir) as entries:
                  for entry in entries:
                     if entry.is_file():
                        os.unlink(entry.path)
                     else:
                        shutil.rmtree(entry.path)
               print("All files and subdirectories deleted successfully.")
            except OSError:
               print("Error occurred while deleting files and subdirectories.")


def prepare_file_contents(file_to_be_changed, value):   
         for headerGuard in fileinput.input(file_to_be_changed, inplace=True):
            headerGuard = headerGuard.replace('NONAME_H', (value + '_H').upper())
            sys.stdout.write(headerGuard) 

         for l in fileinput.input(file_to_be_changed, inplace=True):
            l = l.replace('NoName', value)
            sys.stdout.write(l)     

def generate_bash(path, script_name, subject, build_name):
            if subject == 'tarball':
               bash_file = open(path + '/' + script_name + '_tar.sh','a')
               bash_file.write('!#bin/bash') 
               bash_file.write('\nuser=$(whoami)') 
               bash_file.write('\nPathToFolder=/home/$user/StandGUI')  
               bash_file.write('\nDateOfTar=$(date +%Y-%m-%d)')  
               bash_file.write('\ntar -cvf StandGUI.$DateOfTar.tar $PathToFolder')  
            if subject == 'build copying':
               bash_file = open(path + '/' + script_name + '_copy.sh','a')
               bash_file.write('!#bin/bash\n')     
               bash_file.write('user=$(whoami)\n')
               bash_file.write('cd /home/$user/' + script_name + '\n')
               bash_file.write('cp lib' + script_name + '.so /home/$user/.oper_vis/plugins/')
            bash_file.close()
         
               # bash_file.write('\nboboooooo')  