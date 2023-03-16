#include "Node.h"
int depthValue=INT_MIN;//extra
void firstPage(trie *head);
trie* getNewNode()
{
    trie* node=new trie;
    node->isLeaf=0;
    for(int i=0;i<ALPHABET_SIZE;i++)
    {
        node->children[i]=NULL;
    }
return node;
}
void depth(string str)
{
    
int len=str.length();
if(len>depthValue)
{
    depthValue=len;
}

}
trie* insert(trie *head,string str)
{
    //for depth, when giving the user the option to append or insert the depth is to be updated
    depth(str);//to know the depth of the trie
   
    char c;
    trie* curr=head;//start from the root
    if(head==NULL)
    {
        cout<<"error"<<endl;
    }
    try{
    for(int i=0;i<str.length();i++)
    {
        c=str[i];//we take each character to make a trie
        if(curr->children[c-'a']==NULL)//if the letter in that node 26 options of children is not full(or empty), we 
        //create one which now can be used for similar type
        
        {
            curr->children[c-'a']=getNewNode();
        }
        curr=curr->children[c-'a'];//is empty, increament until end of str is not reached
        
    }
    }catch(bad_alloc& e)
    {
        //cout<<"here";
        throw MemoryAllocationError();
    }
    if(curr!=NULL)
    {curr->isLeaf=1;}//check for exception
    return(curr);//return the current position node
    
}
trie* insert_from_file(trie *head,string str)
{
    str.pop_back();//this is to remove extra space which is stored in word of each node
    depth(str);//to know the depth of the trie
    trie* result=insert(head,str);
    return result;
}

trie* search(trie *head,string str)
{
    if(head==NULL)
    {
        return 0;
    }
    trie *curr=head;
    char c;
    int len=str.length();
    for(int i=0;i<str.length();i++)
    {
        c=str[i];
        curr=curr->children[c-'a'];//until the end of string is not reached, we move in the trie
        if(curr==NULL)//check for exception
        {
            return 0;
        }
    }
    return curr;//return required node
}
void read_from_file(trie *head)
{
    
    trie* t;
    string line;
    string Word;
    string Meaning;
    ifstream myfile;
    myfile.open("real_dictionary.txt");
    if(!myfile.is_open())
    {
        cout<<"error while reading"<<endl;
        exit(0);
    }
    
    if(myfile.is_open())
    {
    while(getline(myfile,line))
    {
        try{
        istringstream iline(line);//reads the line in a inputstream iline which is created using istringstream
        getline(iline, Word,'-');//reads the line until and - is encountered and stores the string in Word
        t=insert_from_file(head,Word);//used to insert the word in trie data structure
        t->word=Word;//we insert to the returned node's(which is the last character's node) word the Word to be stored
        getline(iline,Meaning,'\n');//all th other line in the iline till newline is encountered is placed in Meaning
        t->meaning=Meaning;//we store Meaning to t(node)->meaning 
    }catch(MemoryAllocationError& e)
    {
        cout<<"error:"<<e.what()<<endl;
    }
    
    }
    myfile.close();
    /*}catch(MemoryAllocationError& e)
    {
        cout<<"error:"<<e.what()<<endl;
    }*/
    
   
    }
}
void getPrefixHelp(trie *node,string str,vector<string>& result_word,vector<string>& result_meaning)//recursion is used to
//search for words with all prefix
{
    if(node->isLeaf)//if string ends then send the values to vector to store
    {
        result_word.push_back(str);
        result_meaning.push_back(node->meaning);
    }
    for(int i=0;i<ALPHABET_SIZE;i++)
    {
        if(node->children[i]!=nullptr)
        {
            str+=('a'+i);
            getPrefixHelp(node->children[i],str,result_word,result_meaning);//recusrion for checking all possiblility 
            //with prefix
            str.pop_back();
        }
    }
}

void adding_to_file(string word,string meaning,string pos1)
{
    depth(word);
    ofstream outfile("real_dictionary.txt",ios_base::app);
    if(!outfile.is_open())
    {
        cout<<"error to open file"<<endl;
        exit(0);
    }
    outfile<<'\n';//using the format in out txt file
    outfile<<word;
    outfile<<' ';
    outfile<<'-';
    outfile<<' ';
    outfile<<pos1;
    outfile<<'.';
    outfile<<' ';
    outfile<<meaning;
    outfile.close();
}
void deleteTrie(trie *head)//free up the space
{
    if(head==nullptr)
    {
        return;
    }
    for(int i=0;i<26;i++)
    {
        deleteTrie(head->children[i]);
    }
    delete head;
}
int main()
{
    trie* Head=getNewNode();//the head is null always, just used as reference
    read_from_file(Head);//reads .txt file and creates a trie from that document
    firstPage(Head);
    deleteTrie(Head);//deletes all the memory allocated for trie when program terminates
    return 0;
}