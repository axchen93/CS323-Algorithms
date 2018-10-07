#include<fstream>
#include<iostream>
#include<string>

using namespace std;

struct binTreeNode{
    string chStr;
    int prob;
    string code;
    binTreeNode *next, *left, *right;
    
    binTreeNode(){
        chStr = "";
        prob = 0;
        code = "";
        next=NULL;
        left=NULL;
        right=NULL;
    }

    binTreeNode(string s, int p){
        chStr = s;
        prob = p;
        code = "";
        next=NULL;
        left=NULL;
        right=NULL;
    }

    string to_String(){
        binTreeNode *T = this;
        string ans = "(\"" + T->chStr + "\", " + to_string(T->prob) + ", ";
        if(T->next == NULL) ans = ans + "NULL)";
        else ans = ans + "\"" +  T->next->chStr + "\")";
        return ans;
    }

    void printNode(binTreeNode *T, ofstream& out4){
        if(T==NULL) {
            out4 << "NULL" << endl;
            return;
        }
        out4 << "(" << T->chStr << ", " << T->prob << ")---";
        if(T->code == "") out4 << "Code: NULL---";
        else out4 << "Code: " << T->code << "---";
        if(T->next == NULL) out4 << "Next: NULL---";
        else out4 << "Next: " << T->next->chStr << "----";
        if(T->left == NULL) out4 << "Left child: NULL---";
        else out4 << "Left child: " << T->left->chStr << "---";
        if(T->right == NULL) out4 << "Right child: NULL";
        else out4 << "Right child: " << T->right->chStr;

        out4 << endl;
    }
};

class HuffmanListTree{
    private:
    binTreeNode *listHead, *root;

    public:

    HuffmanListTree(){
        binTreeNode *dummy = new binTreeNode("dummy", 0);
        listHead = dummy;
        root = NULL;
    }

    HuffmanListTree(binTreeNode *T){
        binTreeNode *dummy = new binTreeNode("dummy", 0);
        listHead = dummy;
        listHead->next = T;
        root = NULL;
    }

    binTreeNode* getRoot(){
        return root;
    }

    binTreeNode* getListhead(){
        return listHead;
    }

    void constructLinkedList(ifstream& input, ofstream& output){
        string chStr;
        int prob;
        while(input.good()){
            input >> chStr >> prob;
            binTreeNode* spot = findSpot(prob);
            binTreeNode* newNode = new binTreeNode(chStr, prob);
            insertNode(spot, newNode);
            printList(output);
        }
    }

    void constructBinTree(ofstream& out2){
        while(listHead->next->next!=NULL){
            binTreeNode* first = listHead->next;
            binTreeNode* second = first->next;

            int newProb = first->prob + second->prob;
            string newChar = first->chStr +second->chStr;

            binTreeNode *newNode = new binTreeNode(newChar, newProb);
            newNode->left = first;
            newNode->right = second;

            binTreeNode* spot = findSpot(newProb);
            insertNode(spot, newNode);

            listHead->next = second->next;
            newNode->printNode(newNode, out2);
            printList(out2);
        }
        root = listHead->next;
    }

    void constructCode(binTreeNode* T, string code, ofstream& out3){
        if(T==NULL){
            cout << "Empty Tree" << endl;
            exit(1);
        }
        if(isLeaf(T)){
            T->code = code;
            out3 << T->chStr << "- Code: " << T->code << endl;
            return;
        }
        constructCode(T->left, code + "0", out3);
        constructCode(T->right, code + "1", out3);
    }

    binTreeNode* findSpot(int prob){
        binTreeNode* spot = listHead;
        while(spot->next!=NULL && spot->next->prob < prob){
            spot = spot->next;
        }
        return spot;
    }

    void insertNode(binTreeNode* spot, binTreeNode* newNode){
        newNode->next = spot->next;
        spot->next = newNode;
    }

    bool isLeaf(binTreeNode* T){
        return (T->left== NULL && T->right== NULL);
    }

    void printList(ofstream& output){
        binTreeNode* current = listHead;
        output << "Listhead ---> " << current->to_String();
        current = current->next;
        while(current!=NULL){
            output << " ---> " << current->to_String();
            current = current->next;
        }
        output << "---> NULL\n";
    }

    static void preOrder(binTreeNode *T, ofstream& out4){
        if(T==NULL) return;
        T->printNode(T, out4);
        preOrder(T->left, out4);
        preOrder(T->right, out4);
    }
    static void postOrder(binTreeNode *T, ofstream& out4){
        if(T==NULL) return;
        preOrder(T->left, out4);
        preOrder(T->right, out4);
        T->printNode(T, out4);
    }
    static void inOrder(binTreeNode *T, ofstream& out4){
        if(T==NULL) return;
        preOrder(T->left, out4);
        T->printNode(T, out4);
        preOrder(T->right, out4);
    }
};

int main(int argc, char** argv){
    ifstream input;
    ofstream output1, output2, output3, output4;

    input.open(argv[1]);    
    output1.open(argv[2]);   
    output2.open(argv[3]);   
    output3.open(argv[4]);   
    output4.open(argv[5]);   


    HuffmanListTree* huffman = new HuffmanListTree();

    huffman->constructLinkedList(input, output1);
    output1.flush();
    huffman->constructBinTree(output2);
    output2.flush();
    huffman->constructCode(huffman->getRoot(), "", output3);
    output3.flush();
    output4 << "Preorder: \n";
    HuffmanListTree::preOrder(huffman->getRoot(), output4);
    output4 << "\nInorder: \n";
    HuffmanListTree::inOrder(huffman->getRoot(), output4);
    output4 << "\nPostorder: \n";
    HuffmanListTree::postOrder(huffman->getRoot(), output4);
    output4.flush();

    input.close();
    output1.close();
    output2.close();
    output3.close();
    output4.close();

    return 0;
}
