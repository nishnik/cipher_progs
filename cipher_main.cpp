//TODO: PLAYFAIR CIPHER DECRYPTION
//TODO: ADD INFO
#include <iostream>
#include "cipher_functions.hh"

using namespace std;

int main()
{
	cipher C;
	cout<<"\nWelcome";
	while(1)
	{
		cout<<"\n 1. Caesar Cipher";
		cout<<"\n 2. Affine Cipher";
		cout<<"\n 3. Vigenere Cipher";
		cout<<"\n 4. Hill Cipher";
		cout<<"\n 5. Transposition Cipher";
		//cout<<"\n 6. Playfair Cipher";
		cout<<"\n 6. Quit";
		cout<<"\nEnter Choice: ";
		int a=0;
		cin>>a;
		switch(a){
			case 6:
			return 0;break;
			//case 6:
			//C.playfair_cipher();break;
			case 5:
			C.transposition_cipher();break;
			case 4:
			C.hill_cipher();break;
			case 3:
			C.vigenere_cipher();break;
			case 2:
			C.affine_cipher();break;
			case 1:
			C.caesar_cipher();break;
			default:
			cout<<"\n Enter valid entry.";
		}

	}
}
