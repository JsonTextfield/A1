import java.util.Scanner; 
public class a1{
    public static void main(String[] args){
        while(true){
        a1 program = new a1();
        int choice;
        Scanner sc = new Scanner(System.in);
        
            System.out.print("You may:\n\t(1) Encrypt a message\n\t(2) Decrypt a message\nWhat is your selection: ");
            choice = Integer.parseInt(sc.nextLine());
            char key;
            int counter = 0;
            switch(choice){
                case 1:
                    System.out.println(" Enter a plaintext message\n");
                    String message = sc.nextLine();
                    System.out.println(" Enter a numeric key (0-255)\n");
                    key = (char)sc.nextInt();
                    if(key < 0 || key > 255){
                        System.out.println("You did not enter a valid key");
                        break;
                    }
                    for(char x : message.toCharArray()){
                        System.out.printf("%d ", (int)program.encode(x, key, counter));
                        counter++;
                    }
                    System.out.print("\n");
                    break;
                case 2:
                    System.out.println("Enter a ciphertext message");
                    String entry = sc.nextLine();
                    String[] code = entry.split(" ");
                    System.out.println(" Enter a numeric key (0-255)");
                    key = (char)sc.nextInt();
                    if (key < 0 || key > 255){
                        System.out.println("You did not enter a valid key");
                        break;
                    }
                    for(String x : code){
                        System.out.printf("%c", program.encode((char)Integer.parseInt(x), key, counter));
                        counter++;
                    }
                    System.out.println("");
                    break;
                default:
                    System.out.println("NO");
                    break;
                
            }
        }
    }
    public char encode(char source, char key, int counter){
        char resultingByte = source;
        if(counter%3 == 0){
            for(int x = 0; x < 8; x += 2){
                if((getBit(source, x) ^ getBit(key, x)) == 0){
                    resultingByte = clearBit(resultingByte, x);      
                }
                if((getBit(source, x) ^ getBit(key, x)) == 1){
                    resultingByte = setBit(resultingByte, x);
                }
            }
        }
        if(counter%3 == 1){
            for(int x = 1; x < 8; x += 2){
                if((getBit(source, x) ^ getBit(key, x)) == 0){
                    resultingByte = clearBit(resultingByte, x);      
                }
                if((getBit(source, x) ^ getBit(key, x)) == 1){
                    resultingByte = setBit(resultingByte, x);
                }
            }
        }
        if(counter%3 == 2){
            for(int x = 0; x < 8; x++){
                if((getBit(source, x) ^ getBit(key, x)) == 0){
                    resultingByte = clearBit(resultingByte, x);      
                }
                if((getBit(source, x) ^ getBit(key, x)) == 1){
                    resultingByte = setBit(resultingByte, x);
                }
            }
        }
        return resultingByte;
    }
    public char clearBit(char c, int n){
        c = (char)(c & (c ^ (1 << n)));
        return c;
    }
    public char setBit(char c, int n){
        c = (char)(c | (1 << n));
        return c;
    }
    public char getBit(char c, int n){
        return (char)(((int)c >>> n) & 1);
    }
}