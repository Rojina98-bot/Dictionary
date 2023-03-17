#include "Node.h"
void firstPage(trie *head);
trie* CreateNode()
{
    trie* node=new trie();
    if(node==NULL)//null before giving null
    {
        cout<<"error allocating memory";

    }
    int isLeaf=0;
    for(int i=0;i<ALPHABET_SIZE;i++)
    {
        node->children[i]=NULL;
    }
    node->word="";
    node->meaning="";
    return node;
}
trie* insert(trie* head,string str)
{
    char c;
    if(head==nullptr)
    {
        cerr<<"failed to allocate memory for head";
    }
    trie *curr=head;
    for(int i=0;i<str.length();i++)
    {
        c=str[i];
        if(curr->children[c-'a']==NULL)
        {
            curr->children[c-'a']=CreateNode();
        }
        curr=curr->children[c-'a'];
    }
    curr->isLeaf=1;
    return curr;
   
}
trie *search(trie *head,string str)
{
    if(head==nullptr)
    {
        cerr<<"failed to allocate memory for head";
    }
    trie *curr=head;
    char c;
    for(int i=0;i<str.length();i++)
    {
        c=str[i];
        curr=curr->children[c-'a'];
        if(curr==NULL)
        {
            cout<<"error, no such word";//check for error input
        }
    }
    return curr;

}
void getPrefixHelp(trie *t,string key,vector<string>& result_word,vector<string>& result_meaning)
{
    if(t->isLeaf)
    {
        result_word.push_back(key);
        result_meaning.push_back(t->meaning);
    }
    for(int i=0;i<ALPHABET_SIZE;i++)
    {
        if(t->children[i]!=nullptr)
        {
            key+=('a'+i);
            getPrefixHelp(t->children[i],key,result_word,result_meaning);
            key.pop_back();
        }
    }
}
pair<vector<string>, vector<string>> searchPrefix(trie *head,string key)//,vector<string>result_word,vector<string>result_meaning)
{
    vector<string>result_word;
    vector<string>result_meaning;
    if(head==nullptr)
    {
        cerr<<"failed to allocate memory for head";
    }
    trie *t;
    t=search(head,key);
    if(t==NULL)//for error condition
    {
        cout<<"prefix does not exist";
        return make_pair(vector<string>(),vector<string>());
    }
    getPrefixHelp(t,key,result_word,result_meaning);
    return make_pair(result_word,result_meaning);

}
void read_from_file(trie *head)
{
    trie *t;
    string line,word,meaning;
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
            istringstream iline(line);//reads the line in a inputstream iline which is created using istringstream
            getline(iline,word,'-');//reads the line until and - is encountered and stores the string in word
            word.pop_back();//to remove space
            t=insert(head,word);//used to insert the word in trie data structure
            t->word=word;
            getline(iline,meaning,'\n');//all th other line in the iline till newline is encountered is placed in meaning
            t->meaning=meaning;
        }
    }
    myfile.close();
}
void add_to_file(string word,string meaning,string pos1)
{
    ofstream outfile("real_dictionary.txt",ios_base::app);
    if(!outfile.is_open())
    {
        cout<<"error while writing to file";
        return;
    }
    outfile<<word;//for formatting
    outfile<<' ';
    outfile<<'-';
    outfile<<' ';
    outfile<<pos1;
    outfile<<'.';
    outfile<<' ';
    outfile<<meaning;
    outfile<<'\n';
    outfile.close();
}
void replace(trie *head,string word,string meaning,string pos1)//replace old meaning and pos with new values
{
    trie *t;
    t=search(head,word);
    t->meaning=pos1+"."+" "+meaning;
    string line,word_file,meaning_file;
    ifstream inputfile("real_dictionary.txt");
    ofstream outfile("temp.txt");
    if(!inputfile.is_open())
    {
        cerr<<"error reading file"<<endl;
    }
    if(inputfile.is_open())
    {
        while(getline(inputfile,line))
        {
            istringstream iline(line);
            getline(iline,word_file,'-');
            word_file.pop_back();
            if(word!=word_file)
            {
                getline(iline,meaning_file,'\n');
                outfile<<word_file;
                outfile<<' ';
                outfile<<'-';
                outfile<<meaning_file;
                outfile<<'\n';
            }
        }
    }
    inputfile.close();
    outfile.close();
    remove("real_dictionary.txt");
    rename("temp.txt","real_dictionary.txt");//first deleting previous value
    add_to_file(word,meaning,pos1);//then adding new values
    
}
void deleteTrie(trie* head)//deleting after program ends
{
    if(head==nullptr)
    {
        return;
    }
    for(int i=0;i<ALPHABET_SIZE;i++)
    {
        deleteTrie(head->children[i]);
    }
    delete head;
}
int main()
{
    trie *head=nullptr;
    head=CreateNode();
    trie *t;
    read_from_file(head);
    firstPage(head);
    deleteTrie(head);
    return 0;
}