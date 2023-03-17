#include"Node.h"
pair<vector<string>, vector<string>> searchPrefix(trie *head,string key);
trie* CreateNode();
void add_to_file(string word,string meaning,string pos1);
trie* insert(trie* head,string str);
trie *search(trie *head,string str);
void replace(trie *head,string word,string meaning,string pos1);
bool alreadyThere(string key)//to check whether word already exists or not
{
    string line,word;
    ifstream myfile;
    myfile.open("real_dictionary.txt");
    if(!myfile.is_open())//check in case file cannot open
    {
        cerr<<"error reading file"<<endl;
    }
    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            istringstream iline(line);
            getline(iline,word,'-');
            word.pop_back();
            if(word==key)
            {
                return true;
            }
        }
    }
    myfile.close();
    return false;
}
void preSearch(trie *head)//prefix search
{
    system("cls");
    string key;
    vector<string>result_word;
    vector<string>result_meaning;
    cout<<"\t\t   ###########################"<<"\t\t ?:new key  |  b:main page"<<endl;
    cout<<"\t\t(  )\tEnter the key"<<endl;
    cout<<"\t\t / ###########################"<<"\t\t\t enter everthing in lower alphabet and no symbols"<<endl;
    cin>>key;
    auto twoVecs=searchPrefix(head,key);//returns two vectors containing words with same prefix and their meaning
    if(twoVecs.first.empty()&&twoVecs.second.empty())
    {
        return;
    }
    result_word=twoVecs.first;
    result_meaning=twoVecs.second;
    cout<<setw(20)<<"WORD:"<<"\t\t\t"<<"MEANING:"<<endl<<endl;
    for(int i=0;i<result_word.size();i++)
    {
        cout<<setw(20)<<result_word[i]<<"\t\t\t"<<result_meaning[i]<<endl;

    }
    cout<<endl;
    cout<<endl<<"\t\t ?:new key  |  b:main page"<<endl;
}
void insertDesign(trie *head)//inserting word
{
    bool ans;
    string new_meaning, new_pos;
    trie *t=CreateNode();
    system("cls");
    string word,meaning,pos1;
    char choice,input;
    cout<<"######################"<<"\t\t ?:new key  |  b:main page"<<endl;
    cout<<"\tWORD"<<endl;
    cout<<"######################"<<"\t\t\t enter everthing in lower alphabet and no symbols"<<endl<<endl;
    cin.ignore();
    getline(cin,word);
    cout<<endl<<endl;
    ans=alreadyThere(word);//check if word exists or not
    if(ans==true)
    {
        cout<<"The word already exists"<<endl;
        cout<<"pls add a new word or do you want to replace it with differnt meaning and pos"<<endl;
        cout<<"a:add   | r:replace"<<endl;
        cin>>input;
        if(input=='a')//option to add new word
        {
            cout<<"?\b\b\b\b?:new key  |  b:main page"<<endl;
            return;
            
        }
        else if(input=='r')//replace with new meaning and pos
        {
            cout<<endl<<"meaning:"<<endl;
            cin.ignore();
            getline(cin,new_meaning);
            cout<<endl<<"part of speech"<<endl;
            cin>>new_pos;
            replace(head,word,new_meaning,new_pos);
            cout<<endl;
            
           
        }
        else
        {
            cout<<"invalid option:";
            

        }
        cout<<"?\b\b\b\b?:new key  |  b:main page"<<endl;
        return;
    }
    cout<<"######################"<<endl;
    cout<<"\t MEANING"<<endl;
    cout<<"######################"<<endl<<endl;
    getline(cin,meaning);
    cout<<endl<<endl;
    cout<<"######################"<<endl;
    cout<<" part of speech "<<endl;
    cout<<"######################"<<endl<<endl;
    cin>>pos1;
    add_to_file(word,meaning,pos1);// add new word to file
    t=insert(head,word);//and trie also
    t->word=word;
    t->meaning=pos1+"."+" "+meaning;//in specific format
    cout<<endl;
    cout<<"?\b\b\b\b?:new key  |  b:main page"<<endl;

}
void searchWord(trie *head)
{
    system("cls");
    trie *t;
    string str;
    char choice;
    cout<<"\t\t  ###########################"<<"\t\t ?:new key  |  b:main page"<<endl;
    cout<<"\t\t(  )\tenter the key"<<endl;
    cout<<"\t\t / ###########################"<<"\t\t\t enter everthing in lower alphabet and no symbols"<<endl;
    cin>>str;
    t=search(head,str);
    if(t==NULL)
    {
        return;
    }
    cout<<endl;
    cout<<"WORD:\t\t MEANING:"<<endl;
    cout<<t->word<<"\t\t"<<t->meaning<<endl;
    cout<<endl;
    cout<<"?\b\b\b\b?:new key  |  b:main page"<<endl;
}
char coverPage()
{
    char userInput;
    system("cls");
    cout << "\033[32m"; // Set text color to green
    cout<<"\t\t\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<" \t\t\t\t\t\tOXFORD DICTIONARY "<<endl;
    cout<<"\t\t\t\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl<<endl<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t |\t\t's' for search for prefix    |"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t |\t\t 'i' for insert\t\t     |"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t |\t\t 'w' for word\t\t     |"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t *********************************************"<<endl;
    cout<<"\t\t |\t\t'e' for exit \t\t     |"<<endl;
    cout<<"\t\t *********************************************"<<endl<<endl<<endl;
    cout<<"CHOICE"<<endl;
    cout<<"||||||||||||||||||||||||||||||"<<endl;
    cin>>userInput;
    cout<<"||||||||||||||||||||||||||||||"<<endl;
    return userInput;
}
void firstPage(trie *head)
{
    char userInput,choice;
    userInput=coverPage();//for the first time, not keeping in loop
    while(userInput!='e')
    {
    switch(userInput)
    {
    
        case 's':
        { 
            system("cls");
            preSearch(head);
            cin>>choice;
            while(choice!='b')
            {
                if(choice=='?')
                {
                    preSearch(head);
                }
                else
                {
                    cout<<"invalid option,enter again:"<<endl;
                }
                cin>>choice;
               
            }
            break;

        }
        case 'i':
        {
            system("cls");
            insertDesign(head);
            cin>>choice;
            while(choice!='b')
            {
                if(choice=='?')
                {
                    insertDesign(head);
                }
                else
                {
                    cout<<"invalid option,enter again:"<<endl;
                }
                cin>>choice;
               
            }
            break;


        }
        case 'w':
        {
            system("cls");
            searchWord(head);
            cin>>choice;
            while(choice!='b')
            {
                if(choice=='?')
                {
                    searchWord(head);
                }
                else
                {
                    cout<<"invalid option,enter again:"<<endl;
                }
                cin>>choice;
               
            }
            break;
        }

        default:
        {
        cout<<"invalid";
        break;
        }
        
    }
    userInput=coverPage();//this is called until 'e' exit is pressed
    }


}
