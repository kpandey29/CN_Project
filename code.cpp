/*
*@brief A program to validate a given IP address which is 
given in dotted notation along with mask and generate first 
and last address along with three random address blocks with 
the same size
*@Executing instruction : g++ code.cpp && ./a.out 
*/
#include<bits/stdc++.h>
using namespace std;

    /*To check the validity of the ip */
    bool isvalid(vector<string> arr){
        int x;
        for(int i=0;i<4;i++){
            x=stoi(arr[i]);//convert string to integer
            if(x<0||x>255)//checking the range of the ip address
                return false;
        }
        return true;
    }
    //To convert the binary representation of ip address to its decimal form
    string func(int arr[]){
        int val=0;
        string bottom="";
        int i=0;
        /*Now,we are dealing with the first octet*/
        for(int j=7;j>=0;j--){
            double temp=pow(2,i);//converting the binary to decimal
            int x=(int)temp;//typecasting to int
            val+=(x*arr[j]);/*Storing the decimal equivalent in val*/
            i++;
        }
        string f=to_string(val);
        bottom+=f;
        bottom+=".";//to represent in the ip format
        val=0;
        i=0;
        /*Now,we are dealing with the second octet*/
        for(int j=15;j>7;j--){
            double temp=pow(2,i);
            int x=(int)temp;
            val+=(x*arr[j]);
            i++;
        }
        f=to_string(val);
        bottom+=f;
        bottom+=".";
        val=0;
        i=0;
        /*Now,we are dealing with the third octet*/
        for(int j=23;j>15;j--){
            double temp=pow(2,i);
            int x=(int)temp;
            val+=(x*arr[j]);
            i++;
        }
        f=to_string(val);
        bottom+=f;
        bottom+=".";
        val=0;
        i=0;
        /*Now,we are dealing with the fourth octet*/
        for(int j=31;j>23;j--){
            double temp=pow(2,i);
            int x=(int)temp;
            val+=(x*arr[j]);
            i++;
        }
        f=to_string(val);
        bottom+=f;
        val=0;
        i=0;
        return bottom;//returning the string in ip representation*/
    }
 
void splitstr(string str, string deli,vector<string> &valid)
{
    int start = 0;
    int end = str.find(deli);
    while (end != -1) {
        valid.push_back(str.substr(start, end - start));//pushing the substring till delimiter
        start = end + deli.size();//setting start to the new position after delimiter
        end = str.find(deli, start);//finding the next delimiter
    }
    valid.push_back(str.substr(start, end - start));//pushing the last substring
}

string DecimalToBinaryString(int a)
{
    string binary = "";
    int mask = 1;
    for(int i = 0; i < 31; i++)
    {
        if((mask & a) != 0)
            binary = "1"+binary;
        else
            binary = "0"+binary;
        mask<<=1;
    }
    return binary;
}
    
     int main(){
        cout<<"\n***********Welcome to the IP Address Calculator***********"<<endl;
        cout<<"\nEnter the ip address in the format x.x.x.x : ";
        string str1;//to store the ip address in string format
        cin>>str1;
        cout<<"\nEnter the subnet mask in integer form: ";
        int mask;
        cin>>mask;//it has been taken in an integer format
       vector<string> valid;
        splitstr(str1, ".",valid);

        if(isvalid(valid))
        {
            cout<<"\nThe entered IP address is Valid"<<endl;
        }
        else{
            cout<<"\nThe entered IP address is Invalid"<<endl;
            return 0;
        }
        int arr1[32];//to store the binary representation of the ip address
        for(int i=0;i<4;i++){
            int temp=stoi(valid[i]);
            string binary=DecimalToBinaryString(temp);
            /*storing the first octet's binary representation*/
            if(i==0){
                int j=7;
                int x=binary.length();
                x--;
                while(x>=0&&j>=0){
                    char temp2=binary[x];
                    if(temp2=='0')
                    arr1[j--]=0;
                    else
                    arr1[j--]=1;
                    x--;
                }
            }
            //dealing with the second octet
            else if(i==1){
                int j=15;
                int x=binary.length();
                x--;
                while(x>=0&&j>=8){
                    char temp2=binary[x];
                    if(temp2=='0')
                    arr1[j--]=0;
                    else
                    arr1[j--]=1;
                    x--;
                }
            }
            //dealing with the third octet
            else if(i==2){
                int j=23;
                int x=binary.length();
                x--;
                while(x>=0&&j>=16){ 
                    char temp2=binary[x];
                    if(temp2=='0')
                    arr1[j--]=0;
                    else
                    arr1[j--]=1;
                    x--;
                }
            }
            //dealing with the fourth octet
            else if(i==3){
                int j=31;
                int x=binary.length();
                x--;
                while(x>=0&&j>=24){
                    char temp2=binary[x];
                    if(temp2=='0')
                    arr1[j--]=0;
                    else
                    arr1[j--]=1;
                    x--;
                }
            }
        }
        int first[32];//to store the first address
        int last[32];//to store the last address
        //storing the same bit sequence till the mask
        for(int i=0;i<mask;i++){
            first[i]=arr1[i];
            last[i]=arr1[i];
        }
        for(int i=mask;i<32;i++){
            first[i]=0;//for obtaining the first address
            last[i]=1;//for obtaining the last address
        }
        int randomAddFirst[32];
        int randomAddLast[32];

        string first_address=func(first);//converting the first address to ip format
        cout<<"First address: "<<first_address<<endl;
        string last_address=func(last);//converting the last address to ip format
        cout<<"Last address: "<<last_address<<endl;

        double range = pow(2,32-mask);//calculating the range of addresses
        int r=(int)range;
        cout<<"Number of addresses in the block: "<<range<<endl;

        //generating three blocks with same block size
        cout<<"\nRANDOM ADDRESS BLOCKS WITH SAME BLOCK SIZE \n"<<endl;/*here block
        size refers to the number of addresses in a block*/
        for(int j=0;j<3;j++){
            for(int i=0;i<mask;i++){
                randomAddFirst[i]=randomAddLast[i]=(int)(rand()%2);
            }
            for(int i=mask;i<32;i++){
                randomAddFirst[i]=first[i];
                randomAddLast[i]=last[i];
            }
            string testFirst=func(randomAddFirst);//converting the first address to ip format
            string testLast=func(randomAddLast);//converting the last address to ip format
            cout<<"\n******************Random Address Block "<<j+1<<"******************\n"<<endl;
            cout<<"First Address: "<<testFirst<<endl;
            cout<<"Last Address: "<<testLast<<endl;
        }
    }