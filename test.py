import Tkinter as tk, tkFileDialog, shutil, os, sys
from Tkinter import *
''' 
def main():
 
    tk.Tk().withdraw() # Close the root window
    try:
        os.rename(tkFileDialog.askopenfilename(),"JSON.txt")
    except WindowsError:
        print "There was an error"
 
if __name__ == "__main__":
    main()'''
master = Tk()
def ncode():
    main(1)
def dcode():
    main(2)
def main(choice):
    while True:
        counter = 0
        if choice == 1:
            msg = " ".join(text.get().split()[:-1])
            key = text.get().split()[-1]
            print text.get().split()[-1]
            if int(key) < 0 or int(key) > 255:
                text.delete(0, END)
                text.insert(END, "You did not enter a valid key")
                break
            o = ""
            for it in list(list(msg)):
                o += str(encode(ord(it), int(key), int(counter)))+" "
                counter += 1
            text.delete(0, END)
            text.insert(END, o)
            break
        elif choice == 2:
            code = text.get()
            if code.rfind("-1") == -1:
                text.delete(0, END)
                text.insert(END, "You need to enter -1 at the end of your ciphertext")
                break
            code = text.get().split(" ")[:-1]
            key = text.get().split()[-1]
            if int(key) < 0 or int(key) > 255:
                text.delete(0, END)
                text.insert(END,"You did not enter a valid key")
                break
            k = ""
            for it in code:
                if it == "-1":
                    break
                else:
                    k += chr(encode(int(it), int(key), counter))
                counter += 1
            text.delete(0, END)
            text.insert(END, k)
            break
def encode(source,key,counter):
    result = source
    if counter%3 == 0:
        for x in range(0,8,2):
            if(get_bit(source, x) ^ get_bit(key, x) == 0):
                result = clear_bit(result, x)
            if(get_bit(source, x) ^ get_bit(key, x) == 1):
                result = set_bit(result, x)
    if counter%3 == 1:
        for i in range(1,8,2):
            if(get_bit(source, i) ^ get_bit(key, i) == 0):
                result = clear_bit(result, i)
      
            if(get_bit(source, i) ^ get_bit(key, i) == 1):
                result = set_bit(result, i)
    if counter%3 == 2 :
        for x in range(8):
            if(get_bit(source, x) ^ get_bit(key, x) == 0):
                result = clear_bit(result, x)      
      
            if(get_bit(source, x) ^ get_bit(key, x) == 1):
                result = set_bit(result, x)
    return result

def get_bit(c,n):
    return (c >> n) & 1
def set_bit(c,n):
    c = (c | (1 << n))
    return c
def clear_bit(c,n):
    c = (c & (c ^ (1 << n)))
    return c
text = Entry(master, width=70)
text.pack()
b = Button(master, text="Encode", command=ncode)
h = Button(master, text="Decode", command=dcode)
h.pack()
b.pack()
master.minsize(width=500, height=500)

mainloop()





'''main()'''
