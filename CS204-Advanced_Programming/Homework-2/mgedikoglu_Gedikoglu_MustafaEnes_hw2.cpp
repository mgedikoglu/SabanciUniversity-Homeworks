#include <iostream>
#include <sstream>
using namespace std;

struct node{
    int value;
    node* next;
    
    //default constructor
    node ()
        :value(NULL),next(NULL)
    {}
    
    //constructor
    node (int n, node * p)
        :value(n), next(p)
    {}
};


//PRINT

void printDeletedAppended(node *head,node*deletedHead, int number ){
    cout<<"Deleted nodes: ";
    if (deletedHead==NULL){
        cout<<"None";
    }
    else{
        while(deletedHead!=NULL){
            cout<<deletedHead->value<<" ";
            deletedHead=deletedHead->next;
        }
    }
    cout<<endl;
    cout<<"Appended: "<<number<<endl;
}

void printList(node *head, int number ){
    cout<<"List content: ";
    while(head!=NULL){
        cout<<head->value<<" ";
        head=head->next;
    }
    cout<<endl;
}


//Add node at the end of list
node* addNode(node *head,int number){
    node*t=head;
    if(head==NULL){ //If list is empty
        node *n=new node(number,NULL);
        head=n;
        return head;
    }else{ //If list is not empty
        while(t->next!=NULL){
            t=t->next;
        }
        node *n=new node(number,NULL);
        t->next=n;
        return head;
    }
}

// Cheks if number is already in the list
bool inListCheck(node * head, int number){
    bool check=false;
    while(head!=NULL){
        if(head->value==number){
            check=true;
        }
        head=head->next;
    }
    return check;
}

// Deletes all the nodes in the list at the end of the program
void deleteAll(node*head){
    if(head==NULL){
        cout<<endl<<"The list is empty at the end of the program and nothing is deleted"<<endl<<endl;
    }else{
        cout<<endl<<"All the nodes are deleted at the end of the program: ";
        node*h=head;
        node*t;
        while(h!=NULL){
            cout<<h->value<<" ";
            h=h->next;
        }
        cout<<endl;
        while(head!=NULL){
            t=head->next;
            delete head;
            head=t;
        }
    }
}

//----ASCENDING----
//Deletes notes in ascending order
node* aDeleteNode(node *head,int number){
    node*t=head;
    node *a;
    if(head==NULL){ // If list is empty
        return NULL;
    }else if (head->next==NULL){ // If there is one element in the list
        if(head->value>number){
            delete head;
            head=NULL;
        }
        return head;
    }else{
        if(head->value>number){ // If first item greater than number
            while(head!=NULL){
                t=head->next;
                delete head;
                head=t;
            }
            return head;
        }else{ // If second or later item greater than number
            while(t!=NULL){
                node *tn=t->next;
                while(tn!=NULL){
                    if(tn->value>number){
                        t->next=NULL;
                        while(tn!=NULL){
                            a=tn->next;
                            delete tn;
                            tn=a;
                        }
                    }
                    else{
                        t=tn;
                        tn=tn->next;
                    }
                }
                t=t->next;
            }
        }
        return head;
    }
    return NULL;
}

// Returns a list of deleted nodes (ASCENDING)
node* aDeletedNode(node *head,int number){
    node*t=head;
    if(head==NULL){ // If list is empty
        return NULL;
    }else if (head->next==NULL){ // If there is one element in the list
        if(head->value>number){
            return head;
        }
        return NULL;
    }else{
        if(head->value>number){  // If first item greater than number
            return head;
        }
        else{ // If second or later item greater than number
            while(t!=NULL){
                node *tn=t->next;
                while(tn!=NULL){
                    if(tn->value>number){
                        return tn;
                    }
                    else{
                        tn=tn->next;
                    }
                }
                t=t->next;
            }
        }
        return NULL;
    }
    return NULL;
}

//----DESCENDING----
//Deletes notes in descending order
node* dDeleteNode(node *head,int number){
    node*t=head;
    node *a;
    if(head==NULL){ // If list is empty
        return NULL;
    }else if (head->next==NULL){ // If there is one element in the list
        if(head->value<number){
            delete head;
            head=NULL;
        }
        return head;
    }else{
        if(head->value<number){  // If first item lower than number
            while(head!=NULL){
                t=head->next;
                delete head;
                head=t;
            }
            return head;
        }
        else{ // If second or later item lower than number
            while(t!=NULL){
                node *tn=t->next;
                while(tn!=NULL){
                    if(tn->value<number){
                        t->next=NULL;
                        while(tn!=NULL){
                            a=tn->next;
                            delete tn;
                            tn=a;
                        }
                        return head;
                    }
                    else{
                        t=tn;
                        tn=tn->next;
                    }
                }
                t=t->next;
            }
        }
        return head;
    }
    return NULL;
}

// Returns a list of deleted nodes (DESCENDING)
node* dDeletedNode(node *head,int number){
    node*t=head;
    if(head==NULL){ // If list is empty
        return NULL;
    }else if (head->next==NULL){ // If there is one element in the list
        if(head->value<number){
            return head;
        }
        return NULL;
    }else{ // If first item lower than number
        if(head->value<number){
            return head;
        }
        else{ // If second or later item lower than number
            while(t!=NULL){
                node *tn=t->next;
                while(tn!=NULL){
                    if(tn->value<number){
                        return tn;
                    }
                    else{
                        tn=tn->next;
                    }
                }
                t=t->next;
            }
        }
        return NULL;
    }
    return NULL;
}


int main() {
    string order,numbers;
    int number;
    node *head=NULL;
    
    // First Input
    cout<<"Please enter the order mode (A/D): ";
    cin>>order;
    while (order!="A" && order!="D"){
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"Please enter the order mode again (A/D): ";
        cin>>order;
    }

    // Second Input
    cout<<"Please enter the numbers in a line: ";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    
    getline(cin, numbers);
    istringstream linestream(numbers);
    while(linestream>>number){ // Get each number
        if(order=="A"){
            cout<<endl<<"Next number: "<<number<<endl;
            bool checker=inListCheck(head, number);
            if(checker==true){
                cout<<number<<" is already in the list!"<<endl;
                printList(head, number);
            }else{
                node * deletedNode=aDeletedNode(head, number);
                printDeletedAppended(head, deletedNode, number);
                head=aDeleteNode(head, number);
                head=addNode(head, number);
                printList(head, number);
            }
        }else{
            cout<<endl<<"Next number: "<<number<<endl;
            bool checker=inListCheck(head, number);
            if(checker==true){
                cout<<number<<" is already in the list!"<<endl;
                printList(head, number);
            }else{
                node * deletedNode=dDeletedNode(head, number);
                printDeletedAppended(head, deletedNode, number);
                head=dDeleteNode(head, number);
                head=addNode(head, number);
                printList(head, number);
            }
        }

    }
    deleteAll(head);
    return 0;
}
