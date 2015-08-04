#include <iostream>
#include <string>
#include <vector>
#include "cipher_functions.hh"
#include <cmath>
using namespace std;
long long mod (long long a,long long b)
{
	if(a>=0)
	{
		return a%b;
	}
	else
	{
		return (-1*(a/b)+1)*b+a; 
	}
}
long long inv_mod_supp(long long a,long long b,long long x0=0,long long x1=1)
{
	if(a>b && b!=0)
	{
		long long d=x1;
		x1=(-1*x1)*(a/b)+x0;
		x0=d;
	}
	if(b==0)
		return x0;
	else
		return inv_mod_supp(b,mod(a,b),x0,x1);
}
long long inv_mod(long long a,long long b)//b is the modulo number, a is the operand
{
	long long t=inv_mod_supp(a,b);
	
	if(mod(a*t,b)==1)
	{
		return t;
	}
	else
	{
		t=(1-(b*t))/a;
		return t;
	}
}

long long det(vector<vector<float> > mat, int order)
{
	float ratio;
	for(int i=0;i<order;i++)
		{
			for(int j=0;j<order;j++)
			{
				if(j>i)
				{
					ratio=mat[j][i]/mat[i][i];
					for(int k=0;k<order;k++)
					{
						mat[j][k] -= ratio*mat[i][k];
					}
				
					
				}
				
			}
		}
		float det=1;
		for(int i=0;i<order;i++)
		{
			det*=mat[i][i];
		}
		
		if(isnan(det))
			return 0;
		else
			return (long long)nearbyintf(det);
}


vector<vector<float> > inv_mod_matrix(vector<vector<float> > mat, int order)
{
	vector<vector<float> > inv(order,vector<float>(order));
	for(int i=0;i<order;i++)
	{
		for(int j=0;j<order;j++)
		{
			
			if(i==j)
				inv[i][j]=1;
			else
				inv[i][j]=0;
		}
	}

	for(int i=order-1;i>0;i--)
	{
		if(mat[i-1][0]<mat[i][0])
		{
			for(int j=0;j<order;j++)
			{
				int d=mat[i][j];
				mat[i][j]=mat[i-1][j];
				mat[i-1][j]=d;
				d=inv[i][j];
				inv[i][j]=inv[i-1][j];
				inv[i-1][j]=d;
			}		
		}
	}
	for(int i=0;i<order;i++)
	{
		for(int j=0;j<order;j++)
		{
			if(j!=i)
			{
				float d=mat[j][i]/mat[i][i];
				for(int k=0;k<order;k++)
				{
					mat[j][k]-=(mat[i][k]*d);
					inv[j][k]-=(inv[i][k]*d);
				}
			}
		}
	}
	long long de = det(mat,order);
	long long inv_de = inv_mod(de,26);
	for(int i=0;i<order;i++)
	{
		float d=mat[i][i];
		for(int j=0;j<order;j++)
		{
			inv[i][j]=(float)de*inv[i][j]/d;
			inv[i][j]=mod(inv_de*(long long)inv[i][j],26);
		}
	}
	return inv;

}



long long gcd(long long a,long long b)
{
	if(b==0)
		return a;
	else
		return gcd(b,mod(a,b));
}

void cipher::caesar_cipher()
{
	cout<<"\n 1. Encrypt";
	cout<<"\n 2. Decrypt";
	cout<<"\n Enter choice: ";
	int crypt_choice;
	cin>>crypt_choice;
	if(crypt_choice==1)
	{
		cout<<"\n-------Encryption-------";
		cout<<"\n Enter Message [max length 1000, all small letters]: ";
		//char msg[1000];//change it to string
		string msg;
		cin.ignore();
		getline(cin,msg);
		cout<<"\n Enter shift: ";
		int shift;
		cin>>shift;
		shift=mod(shift,26);
		for(int i=0;i<msg.length();i++)
		{
			if(msg[i]==32)
				continue;
			if(msg[i]+shift<='z')
				msg[i]+=shift;
			else
				msg[i]='a'+shift-('z'-msg[i])-1;
		}
		cout<<"\n Encrypted text is: "<<msg<<endl;
		return;
	}
	if(crypt_choice==2)
	{
		cout<<"\n-------Decryption-------";
		cout<<"\n Enter Message [max length 1000, all small letters]: ";
		string msg;
		cin.ignore();
		getline(cin,msg);
		cout<<"\n 1. Decrypt with specific shift";
		cout<<"\n 2. Decrypt without any specific shift";
		cout<<"\n Enter choice: ";
		int decrypt_choice;
		cin>>decrypt_choice;
		if(decrypt_choice==1)
		{
			cout<<"\n Enter shift: ";
			int shift;
			cin>>shift;
			shift=mod(shift,26);
			for(int i=0;i<msg.length();i++)
			{
				if(msg[i]==32)
					continue;
				if(msg[i]-shift>='a')
					msg[i]-=shift;
				else
					msg[i]='z'-shift+(msg[i]-'a')+1;
			}
			cout<<"\n Decrypted text is: "<<msg<<endl;
			return;	
		}
		else if(decrypt_choice==2)
		{	
			cout<<"\n Possible Deciphers: ";
			int shift=1;
			cout<<"\n 0: "<<msg<<endl;
			for(int s=1;s<=25;s++)
			{
				int shift=1;
				for(int i=0;i<msg.length();i++)
				{

					if(msg[i]==32)
						continue;
					if(msg[i]-shift>='a')
						msg[i]-=shift;
					else
						msg[i]='z'-shift+(msg[i]-'a')+1;
				}
				cout<<"\n "<<s<<": "<<msg<<endl;		
			}
			return;
		}
		
	}

}


void cipher::vigenere_cipher()
{
	cout<<"\n Vigenere Cipher";
	cout<<"\n 1. Encrypt";
	cout<<"\n 2. Decrypt";
	cout<<"\n Enter choice: ";
	int crypt_choice;
	cin>>crypt_choice;
	if(crypt_choice==1)
	{
		cout<<"\n Enter Message [max length 1000, all small]: ";
		string msg;
		cin.ignore();
		getline(cin,msg);
		cout<<"\n Enter Key: ";
		string key;
		getline(cin,key);
		int j=0;
		for(int i=0;i<msg.length();i++)
		{

			if(msg[i]==32)
				continue;
			if(j==key.length())
				j=0;
			int shift=key[j++]-'a';
			if(msg[i]+shift<='z')
				msg[i]+=shift;
			else
				msg[i]='a'+shift-('z'-msg[i])-1;
		}
		cout<<"\n Encrypted text is: "<<msg<<endl;
	}
	if(crypt_choice==2)
	{
		cout<<"\n Enter Message [max length 1000, all small]: ";
		string msg;
		cin.ignore();
		getline(cin,msg);
		cout<<"\n Enter Key: ";
		string key;
		getline(cin,key);
		int j=0;
		for(int i=0;i<msg.length();i++)
		{

			if(msg[i]==32)
				continue;
			if(j==key.length())
				j=0;
			int shift=key[j++]-'a';
			if(msg[i]-shift>='a')
				msg[i]-=shift;
			else
				msg[i]='z'-shift+(msg[i]-'a')+1;
		}
		cout<<"\n Decrypted text is: "<<msg<<endl;	
	}
}

void cipher::affine_cipher()
{
	cout<<"\n Affine Cipher";
	cout<<"\n 1. Encrypt";
	cout<<"\n 2. Decrypt";
	cout<<"\n Enter choice: ";
	int crypt_choice;
	cin>>crypt_choice;
	if(crypt_choice==1)
	{
		cout<<"\n Enter Message [max length 1000, all small]: ";
		string msg;
		cin.ignore();
		getline(cin,msg);
		cout<<"\n Enter shift in form of aX+b.";
		int a=1;
		do
		{
		cout<<"\n Enter a [such that gcd(a,26)=1]: ";cin>>a;
		}while(gcd(a,26)!=1);
		int b;
		cout<<"\n Enter b: ";cin>>b;
		for(int i=0;i<msg.length();i++)
		{

			if(msg[i]==32)
				continue;
			int shift=a*(msg[i]-'a')+b;
			shift=mod(shift,26);
			if(msg[i]+shift<='z')
				msg[i]+=shift;
			else
				msg[i]='a'+shift-('z'-msg[i])-1;
		}
		cout<<"\n Encrypted text is: "<<msg<<endl;
		
	}
	else if(crypt_choice==2)
	{
		cout<<"\n Enter Message [max length 1000, all small]: ";
		string msg;
		cin.ignore();
		getline(cin,msg);
		cout<<"\n Enter shift in form of aX+b.";
		int a=1;
		do
		{
		cout<<"\n Enter a [such that gcd(a,26)=1]: ";cin>>a;
		}while(gcd(a,26)!=1);
		int b;
		cout<<"\n Enter b: ";cin>>b;
		for(int i=0;i<msg.length();i++)
		{

			if(msg[i]==32)
				continue;
			int shift=a*(msg[i]-'a')+b;
			shift=mod(shift,26);
			if(msg[i]-shift>='a')
				msg[i]-=shift;
			else
				msg[i]='z'-shift+(msg[i]-'a')+1;
		}
		cout<<"\n Decrypted text is: "<<msg<<endl;
		
	}
}

void cipher::hill_cipher()
{
	cout<<"\n Hill Cipher";
	cout<<"\n 1. Encrypt";
	cout<<"\n 2. Decrypt";
	cout<<"\n Enter choice: ";
	int crypt_choice;
	cin>>crypt_choice;
	if(crypt_choice==1)
	{
		cout<<"\n Enter Message [max length 1000, all small]: ";
		string msg;
		cin.ignore();
		getline(cin,msg);
		cout<<"\n Enter order of matrix: ";
		int order;
		cin>>order;
		vector<vector<float> > mat(order,vector<float>(order));
		do
		{
			cout<<"Enter the matrix [such that gcd(det(matrix),26)=1] : ";
			for(int i=0;i<order;i++)
			{
				cout<<"\n";
				for(int j=0;j<order;j++)
				{
					cin>>mat[i][j];
					cout<<" ";
				}
			}
		}while(gcd(abs(det(mat,order)),26)!=1);
		for(int i=1;i<=msg.length()%order;i++)
		{
			msg+='x';
		}
		string res_msg;
		for(int k=1;k<=msg.length()/order;k++)
		{
			string msg2=msg.substr((k-1)*order,k*order);
			vector<int> res(order,0);
			for(int i=0;i<order;i++)
			{
				for(int j=0;j<order;j++)
				{
					res[i]=res[i]+(msg2[j]-'a')*mat[j][i];
					res[i]%=26;
				}
				res_msg+=(res[i]+'a');
			}
			
		}
		cout<<"\n Encrypted text is: "<<res_msg;
	}
	if(crypt_choice==2)
	{
		cout<<"\n Enter Message [max length 1000, all small]: ";
		string msg;
		cin.ignore();
		getline(cin,msg);
		cout<<"\n Enter order of matrix: ";
		int order;
		cin>>order;
		vector<vector<float> > mat(order,vector<float>(order));
		do
		{
			cout<<"Enter the matrix [such that gcd(det(matrix),26)=1] : ";
			for(int i=0;i<order;i++)
			{
				cout<<"\n";
				for(int j=0;j<order;j++)
				{
					cin>>mat[i][j];
					cout<<" ";
				}
			}
		}while(gcd(abs(det(mat,order)),26)!=1);
		vector<vector<float> > mat_inv=inv_mod_matrix(mat,order);
		string res_msg;
		for(int k=1;k<=msg.length()/order;k++)
		{
			string msg2=msg.substr((k-1)*order,k*order);
			vector<int> res(order,0);
			for(int i=0;i<order;i++)
			{
				for(int j=0;j<order;j++)
				{
					res[i]=res[i]+(msg2[j]-'a')*mat_inv[j][i];
					res[i]%=26;
				}
				res_msg+=(res[i]+'a');
			}
			
		}
		cout<<"\n Decrypted text is: "<<res_msg;
		
	}
}



void cipher::playfair_cipher()
{
	cout<<"\n Playfair Cipher";
	cout<<"\n 1. Encrypt";
	cout<<"\n 2. Decrypt";
	cout<<"\n Enter choice: ";
	int crypt_choice;
	cin>>crypt_choice;
	cout<<"\n Enter Message [all small]: ";
	string msg;
	cin.ignore();
	getline(cin,msg);
	cout<<"\n Enter Key [all small]: ";
	string key;
	getline(cin,key);
	vector<vector<int> > master_array(5,vector<int>(5));
	vector<int> alpha_check(26,0);
	int k1=0;//for filling master array with key
	int k2=0;
	alpha_check['j'-'a']=1;// j and i are treated as same
	for(int i=0;i<5;i++)
	{
		
		for(int j=0;j<5;j++)
		{
			if(k1<key.length())
			{
				while(alpha_check[key[k1]-'a']!=0 && k1<key.length()-1)
					k1++;
				master_array[i][j]=key[k1];
				alpha_check[key[k1]-'a']=1;
				k1++;
			}
			else
			{
				while(alpha_check[k2]!=0)
					k2++;
				master_array[i][j]='a'+k2;
				alpha_check[k2]=1;
				k2++;
			}
		}
		
	}
	if(crypt_choice==1)
	{
		string res_msg;
		res_msg.resize(msg.length());
		for(int i=0;i<msg.length();i+=2)
		{
			if(i+1==msg.length())
			{

				msg.insert(i,"x");
				res_msg.resize(msg.length());
				
			}
			if(msg[i]==msg[i+1])
			{
				if(msg[i]=='x')
					msg.insert(i+1,"q");
				else
					msg.insert(i+1,"x");
				res_msg.resize(msg.length());
				cout<<msg<<"\n";
				i-=2;
				continue;
			}
			
			pair<int,int> c1,c2;
			int flag=0;
			for(int a=0;a<5 && flag!=2;a++)
			{
				for(int b=0;b<5 && flag!=2;b++)
				{
					if(msg[i]==master_array[a][b])
					{
						c1.first=a;
						c1.second=b;
						flag++;
					}
					else if(msg[i+1]==master_array[a][b])
					{
						c2.first=a;
						c2.second=b;
						flag++;
					}

				}
			}
			if(c1.first==c2.first)
			{
				if(c1.second==4)
					c1.second=0;
				else
					c1.second++;
				if(c2.second==4)
					c2.second=0;
				else
					c2.second++;
				res_msg[i]=master_array[c1.first][c1.second];
				res_msg[i+1]=master_array[c2.first][c2.second];
			}
			else if(c1.second==c2.second)
			{
				if(c1.first==4)
					c1.first=0;
				else
					c1.first++;
				if(c2.first==4)
					c2.first=0;
				else
					c2.first++;
				res_msg[i]=master_array[c1.first][c1.second];
				res_msg[i+1]=master_array[c2.first][c2.second];
			}
			else
			{
				res_msg[i]=master_array[c1.first][c2.second];
				res_msg[i+1]=master_array[c2.first][c1.second];
			}


		}
		cout<<"\n Encrypted text is: "<<res_msg;
	}
	if(crypt_choice==2)
	{
		string res_msg;
		res_msg.resize(msg.length());
		for(int i=0;i<msg.length();i+=2)
		{
			pair<int,int> c1,c2;
			int flag=0;
			for(int a=0;a<5 && flag!=2;a++)
			{
				for(int b=0;b<5 && flag!=2;b++)
				{
					if(msg[i]==master_array[a][b])
					{
						c1.first=a;
						c1.second=b;
						flag++;
					}
					else if(msg[i+1]==master_array[a][b])
					{
						c2.first=a;
						c2.second=b;
						flag++;
					}

				}
			}
			if(c1.first==c2.first)
			{
				if(c1.second==0)
					c1.second=4;
				else
					c1.second--;
				if(c2.second==0)
					c2.second=4;
				else
					c2.second--;
				res_msg[i]=master_array[c1.first][c1.second];
				res_msg[i+1]=master_array[c2.first][c2.second];
			}
			else if(c1.second==c2.second)
			{
				if(c1.first==0)
					c1.first=4;
				else
					c1.first--;
				if(c2.first==0)
					c2.first=4;
				else
					c2.first--;
				res_msg[i]=master_array[c1.first][c1.second];
				res_msg[i+1]=master_array[c2.first][c2.second];
			}
			else
			{
				res_msg[i]=master_array[c1.first][c2.second];
				res_msg[i+1]=master_array[c2.first][c1.second];
			}
		}
		cout<<"\n Decrypted text is: "<<res_msg;
	}
}




void cipher::transposition_cipher()
{
	cout<<"\n Transposition Cipher";
	cout<<"\n 1. Encrypt";
	cout<<"\n 2. Decrypt";
	cout<<"\n Enter choice: ";
	int crypt_choice;
	cin>>crypt_choice;
	cout<<"\n Enter Message [all small]: ";
	string msg;
	cin.ignore();
	getline(cin,msg);
	cout<<"\n Enter Key [numeric]: ";
	int key;
	cin>>key;
	if(crypt_choice==1)
	{
		vector<string> res_msg1(key);
		for(int i=0;i<key;i++)
		{
			int pointer=i;
			while(pointer<msg.length())
			{
				res_msg1[i]+=msg[pointer];
				pointer+=key;
			}

		}
		string res_msg;
		for(int i=0;i<key;i++)
		{
			res_msg+=res_msg1[i];
		}
		cout<<"\n Encrypted text is: "<<res_msg;
	}
	if(crypt_choice==2)//
	{
		int key_eff=ceil((float)msg.length()/key);
		int unshaded=key_eff*key-msg.length();
		vector<string> res_msg1(key_eff);
		int col=0,row=0;
		for(int i=0;i<msg.length();i++)
		{
			res_msg1[col]+=msg[i];
			col+=1;
			if(col==key_eff || (col==key_eff-1 && row>=key-unshaded))
			{
				col=0;
				row+=1;
			}

		}
		string res_msg;
		for(int i=0;i<key_eff;i++)
		{
			cout<<res_msg1[i]<<"\n";
			res_msg+=res_msg1[i];
		}
		cout<<"\n Decrypted text is: "<<res_msg;	
		
	}
}