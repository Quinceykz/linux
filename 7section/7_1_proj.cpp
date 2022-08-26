#include<iostream>
int val_rare,val_0,val_1,val_out = 0;
int *p_val = &val_rare;
typedef struct{
        int val_int;
        float val_float;
        char val_char;
} sFILE;

sFILE test_struct_function(int test_int,float test_float,char test_char)
{
        sFILE test_struct_val;
        test_struct_val.val_int = test_int;
        // ...
        return test_struct_val;
}

int test_pointer(int *p_val_test)
{
        // *p_val_test = *p_val_test + 1;
        (*p_val_test)++;
        return *p_val_test;
}


int test_normal(int val_test)              //val_test = val
{
        val_test++;
        return val_test;
}

int main(void)
{
        using namespace std;   
        val_rare = test_normal(val_rare);                                //val_rare = 0;
        cout<<"val compute by normally "<<val_rare<<endl;                //val_rare = 1;
        val_rare++;
        val_rare = *(&val_rare);
        cout<<"without function "<<val_rare<<endl;                       //val_rare = 2;
        cout<<"address is :"<<p_val<<"///"<<&val_rare<<endl; 
        val_0 = test_pointer(&val_rare);                                 //val_rare = 3;
        val_1 = test_pointer(p_val);                                     //val_rare = 4;
        cout<<"val compute by *(&v) "<<val_0<<endl;
        cout<<"val compute by pointer "<<val_1<<endl;
        cout<<"address is :"<<p_val<<"///"<<&val_rare<<endl;
        return 0;
}
