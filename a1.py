import sys


def main():
    while True:
        print "\nYou may:\n"
        print "  (1) Encrypt a message \n"
        print "  (2) Decrypt a message \n"
        choice = raw_input("\n  what is your selection: ")
        counter = 0
        if choice == "1":
            msg = raw_input("Enter a plaintext message\n")
            key = raw_input("Enter a numeric key (0-255)\n")
            if int(key) < 0 or int(key) > 255:
                print "You did not enter a valid key"
                break
            for it in list(msg):
                print ("%d" %(encode(ord(it), int(key), int(counter)))),
                counter += 1
            break
        elif choice == "2":
            code = raw_input("Enter a ciphertext message.\n")
            key = raw_input("Enter a numeric key (0-255)\n")
            if int(key) < 0 or int(key) > 255:
                print "You did not enter a valid key"
                break
            code = code.split(" ")
            for it in code:
                sys.stdout.write("%c" %(encode(int(it), int(key), counter)))
                counter += 1
            sys.stdout.write("\n")
            break
        else:
            print " You did not enter a valid choice.\n"
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

main()
