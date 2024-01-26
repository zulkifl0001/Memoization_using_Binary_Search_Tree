#include <iostream>
#include <fstream>
#include <chrono>
using namespace std::chrono;
using namespace std;


class Matrix
{
private:
    int data[20][20];

public:
    int SIZE ;
    Matrix(int dim=0); //constructor

    friend bool operator ==(Matrix a, Matrix b){
        bool check= true;
        if (a.SIZE!=b.SIZE){
            return false;
        }
        for(int c=0;c<a.SIZE;c++){
            for(int d=0;d<a.SIZE;d++){
                if (a.data[c][d]!=b.data[c][d]){
                    check= false;
                    break;
                }
            }
        }
        return check;
    }
    friend bool operator <(Matrix a, Matrix b){
        if(a.SIZE<b.SIZE){
            return true;
        }if(a.SIZE==b.SIZE){
        bool check=true;
        for (int c=0;c<a.SIZE;c++){
            for(int d=0;d<a.SIZE;d++){
                if(a.data[c][d]>b.data[c][d]){
                    check=false;
                    break;
                }
            }
        }
        return check;}
        else{
            return false;
        }
    }
    int getter(int i, int j); //method to get values at indices
    void setter(int i, int j,int val); //method to set values at indices
    void print(); //method to print the matrix
    unsigned hash()//method to get hash values
    {
        unsigned hashVal=SIZE;
        for (int b=0;b<SIZE;b++){
            for(int c=0;c<SIZE;c++){
                hashVal=61*hashVal+data[b][c];
            }
        }
        return hashVal%65536;
    }
};


//initializes the matrix as an identity matrix

Matrix::Matrix(int dim) {
    SIZE=dim;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(i==j){
                data[i][j]=1;//when i and j are equal, the location is given a value of 1
            }else{
                data[i][j]=0;//other values are initialized as 0s

            }
        }
    }
}

//takes inputs i(row) and j(column) and returns the integer value at that location
int Matrix::getter(int i,int j) {
    if (0<=i & i<SIZE & 0<=j &j<SIZE){

        return data[i][j];

    }
    else{
        cout<<"invalid range"<<endl;//if i or j are outside the range then an error is printed
    }
}


//takes 3 inputs i(row),j(column) and val(value to be assigned)

void Matrix::setter(int i, int j,int val){

    if (0<=i & i<SIZE & 0<=j &j<SIZE ) {
        data[i][j] = val;
    }
    else{
        cout<<"invalid range"<<endl;//if or j are outside the range then an error is printed
    }

}

//print method for self testing

void Matrix::print(){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            cout<<data[i][j]<<" ";
        }
        cout<<endl;
    }
}


//helper function for determinant
//takes a large matrix and an integer and returns a matrix of size N-1xN-1
//the integer is to tell which column to ignore while making the smaller array
Matrix helper(Matrix b,int x){
    Matrix matrix=Matrix(b.SIZE-1);

    int row=0;

    for (int i=0;i<matrix.SIZE;i++){
        int col=0;
        if(i==x)//skips the iteration when i becomes equal to the column num for which the cofactor is being taken
        {
            continue;
        }
        else{
            for (int j=1;j<matrix.SIZE;j++)//we have j=1 as the first row is always ignored
            {

                matrix.setter(row,col,b.getter(i,j));//sets the values for the smaller array
                col+=1;
            }

        }
        row+=1;
    }

    return matrix;
}


//////////////////BINARY TREE
class BST_Node
{
public :
    BST_Node* left;
    BST_Node* right;
    // Determinant of key matrix is value
    Matrix key;
    long value;
    BST_Node(Matrix a,long b){
        left=NULL;
        right=NULL;
        key=a;
        value=b;
    }
};

class BST{
private:
    BST_Node* head;

public:
    int count=0;
    BST_Node* curr;
    BST(){
        head=NULL;
    }
    //searches the BST to see if the key exists
    bool key_exists(Matrix a){
        curr=head;
        if(head==NULL){
            return false;
        }
        else{
            while(1==1){
                //check to see if root node is the required node
                if(curr->key==a){
                    return true;
                }
                //if less than current node
                if(curr->key<a){
                    //if left node not empty go left
                    if(curr->left!=NULL){
                        curr=curr->left;
                    }else{
                        //if empty, no node with requested key exists
                        return false;
                    }
                }
                else{
                    //check if right node is null
                    if(curr->right!=NULL){
                        curr=curr->right;
                    }
                        //if empty, no node with requested key exists
                    else{
                        return false;
                    }
                }
            }
        }
    }

    //searches the BST for the key loc
    long search(Matrix a){
        curr=head;//start from root node
        while(curr!=NULL){
            //check to see if root node is the required node
            if(curr->key==a){
                return curr->value;
            }
            //if less than current node
            if(curr->key<a){
                //go left
                    curr=curr->left;
            }
            else{
                    //go right
                    curr=curr->right;
                }
            }
    }

    //inserts the det and the matrix into the BST
    void insert(Matrix a,long detA){
        if (head==NULL){
            head=new BST_Node(a,detA);
        }
        else {
            curr=head;
            while (1 == 1) {
                //if the key exists
                if(curr->key==a){
                    break;
                }
                //go left
                if (curr->key < a) {

                    //if left is null insert node
                    if(curr->left==NULL){
                        curr->left=new BST_Node(a,detA);
                        count++;//increacing number of BST nodes added
                        break;
                    }else{
                        curr=curr->left;
                    }
                }
                //go right
                else {
                    //if null insert node
                    if(curr->right==NULL){
                        curr->right=new BST_Node(a,detA);
                        count++;
                    }
                    else{
                        curr=curr->right;
                    }
                }
            }
        }
    }

    //calculates the determinant and adds the matrix and det to the BST
    long treeDet(Matrix a){


            //det functions
            if(a.SIZE==1){
                return a.getter(0,0);//the determinant of a 1x1 matrix is itself
            }

            if(key_exists(a)){
            return search(a);//return matrix if matrix is found
             }
            else {
                int check = 0;//used to see if the value at that column is to be added or subtracted while taking the determinant
                long det = 0;

                for (int i = 0; i < a.SIZE; i++) {

                    if ((i + 2) % 2 == 0) {
                        check = 1;
                    } else {
                        check = -1;
                    }
                    det += check * treeDet(helper(a, i)) * a.getter(i,0);//using the helper function inside determinant recursively to get smaller matrices that can be used to calculate the determinant
                }

                insert(a,det); //add the array and its determinant into the BST
                return det;
            }
        }

};




//helper function to get the total number of rows of the input  matrix
int get_rows(string text){
    ifstream file(text);

    char c;
    int counter=0;
    while (file.get(c)) {
        if(c == '\n'){
            counter++;
        }
    }
    file.close();
    return counter;

}
//function to set values for the input matrix
void setMatrix(string text,Matrix &a){
    ifstream file(text);
    int n;
    int i=0;
    int j=0;
    int counter= get_rows(text)-1;

    while (file >> n) {
        a.setter(i,j,n);
        if(j==counter){
            j=0;
            i++;

        }else {
            j++;
        }
    }
    file.close();
}


int main(){
//making matrices
    Matrix a_1=Matrix(get_rows("0_11.txt"));
    Matrix b_1=Matrix(get_rows("1_11.txt"));
    Matrix c_1=Matrix(get_rows("2_11.txt"));
    Matrix d_1=Matrix(get_rows("3_11.txt"));
    Matrix e_1=Matrix(get_rows("4_11.txt"));

    Matrix a_2=Matrix(get_rows("0_12.txt"));
    Matrix b_2=Matrix(get_rows("1_12.txt"));
    Matrix c_2=Matrix(get_rows("2_12.txt"));
    Matrix d_2=Matrix(get_rows("3_12.txt"));
    Matrix e_2=Matrix(get_rows("4_12.txt"));

    Matrix a_3=Matrix(get_rows("0_13.txt"));
    Matrix b_3=Matrix(get_rows("1_13.txt"));
    Matrix c_3=Matrix(get_rows("2_13.txt"));
    Matrix d_3=Matrix(get_rows("3_13.txt"));
    Matrix e_3=Matrix(get_rows("4_13.txt"));

    Matrix a_4=Matrix(get_rows("0_14.txt"));
    Matrix b_4=Matrix(get_rows("1_14.txt"));
    Matrix c_4=Matrix(get_rows("2_14.txt"));
    Matrix d_4=Matrix(get_rows("3_14.txt"));
    Matrix e_4=Matrix(get_rows("4_14.txt"));

    Matrix a_5=Matrix(get_rows("0_15.txt"));
    Matrix b_5=Matrix(get_rows("1_15.txt"));
    Matrix c_5=Matrix(get_rows("2_15.txt"));
    Matrix d_5=Matrix(get_rows("3_15.txt"));
    Matrix e_5=Matrix(get_rows("4_15.txt"));

//setting vals to the matrices
   setMatrix("0_11.txt",a_1);
    setMatrix("1_11.txt",b_1);
    setMatrix("2_11.txt",c_1);
    setMatrix("3_11.txt",d_1);
    setMatrix("4_11.txt",e_1);

    setMatrix("0_12.txt",a_2);
    setMatrix("1_12.txt",b_2);
    setMatrix("2_12.txt",c_2);
    setMatrix("3_12.txt",d_2);
    setMatrix("4_12.txt",e_2);

    setMatrix("0_13.txt",a_3);
    setMatrix("1_13.txt",b_3);
    setMatrix("2_13.txt",c_3);
    setMatrix("3_13.txt",d_3);
    setMatrix("4_13.txt",e_3);

    setMatrix("0_14.txt",a_4);
    setMatrix("1_14.txt",b_4);
    setMatrix("2_14.txt",c_4);
    setMatrix("3_14.txt",d_4);
    setMatrix("4_14.txt",e_4);

    setMatrix("0_15.txt",a_5);
    setMatrix("1_15.txt",b_5);
    setMatrix("2_15.txt",c_5);
    setMatrix("3_15.txt",d_5);
    setMatrix("4_15.txt",e_5);

    auto start = high_resolution_clock::now();
//adding to BST
BST tree=BST();

//    tree.treeDet(a_1);
//    tree.treeDet(b_1);
//    tree.treeDet(c_1);
//    tree.treeDet(d_1);
//    tree.treeDet(e_1);

//    tree.treeDet(a_2);
//    tree.treeDet(b_2);
//    tree.treeDet(c_2);
//    tree.treeDet(d_2);
//    tree.treeDet(e_2);

//    tree.treeDet(a_3);
//    tree.treeDet(b_3);
//    tree.treeDet(c_3);
//    tree.treeDet(d_3);
//    tree.treeDet(e_3);

//    tree.treeDet(a_4);
//    tree.treeDet(b_4);
//    tree.treeDet(c_4);
//    tree.treeDet(d_4);
//    tree.treeDet(e_4);

//tree.treeDet(a_5);
// tree.treeDet(b_5);
//   tree.treeDet(c_5);
//    tree.treeDet(d_5);
//    tree.treeDet(e_5);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout<<duration.count()<<endl;

    cout<<tree.count*sizeof(BST_Node)<<endl;

}