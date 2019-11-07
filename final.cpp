#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <tuple>
#include <regex>
#include <sstream>
#include <cstdlib>
using namespace std;

int order = 3;

class Node {
    public:
        string greeting;
        int nNodes; //number of nodes
        Node *parentNode; 
        Node *next;
        Node *prev;
        vector<tuple<double,string>> record;
        vector<double> keys;
        vector<Node*> children;
        bool isleaf;
        
        Node(bool leaf = true){
            nNodes = 0;
            parentNode = NULL;
            next = NULL;
            prev = NULL;
            greeting = "alive";
            isleaf = leaf ;
        }
};

Node *rootNode = new Node();


bool childSort(const Node* a, const Node* b) { //Sorts the children of node
    // cout<<a->parentNode
    return get<0>(a->record.at(0)) < get<0>(b->record.at(0));
}

bool keySort(const Node*a, const Node* b) { //Sorts the keys of the node
    return a->keys.at(0) < b->keys.at(0);
}

void splitNode(Node *curNode) {
    if (curNode->isleaf) {
        Node *rNode = new Node();
        //curNode->next = rNode;
        rNode->prev = curNode;
        if (curNode->next == NULL) {
            curNode->next = rNode;
        }
        else {
            rNode->next = curNode->next;
            rNode->next->prev = rNode;
            curNode->next = rNode;
        }
        int x = order/2;
        //cout<< x << endl;
        //cout << curNode->record.size() << endl;
        for (int i = curNode->record.size()/2; i<curNode->record.size(); i++)
            rNode->record.push_back(curNode->record.at(i));
        rNode->nNodes = rNode->record.size();
        //cout << rNode->record.size() << endl;
        int z = curNode->record.size() - curNode->record.size()/2;
        curNode->record.erase(curNode->record.begin() + curNode->record.size()/2, curNode->record.end());
        curNode->nNodes = curNode->record.size();
        //cout << curNode->record.size() <<endl;    
        
        // sort(rNode->record.begin(),rNode->record.end());
        // cout << get<0>(rNode->record.at(0));
        if (curNode->parentNode == NULL) {
            Node *pNode = new Node(false);
            pNode->children.push_back(curNode);
            pNode->children.push_back(rNode);
            curNode->parentNode = pNode;
            rNode->parentNode = pNode;
            pNode->keys.push_back(get<0>(rNode->record.at(0)));
            curNode->parentNode->nNodes++;
            //cout<< pNode->keys.at(0)<<endl;
            rootNode = pNode;
            //cout<< rootNode->keys.at(0)<<endl;
            
        }
        else {
            //cout << "hello this is else";
            rNode->parentNode = curNode->parentNode;
           
            curNode->parentNode->keys.push_back(get<0>(rNode->record.at(0)));
            
            sort(curNode->parentNode->keys.begin(),curNode->parentNode->keys.end());
            // for (int i = 0; i< curNode->parentNode->keys.size(); i++)
            //         cout<<curNode->parentNode->keys.at(i)<<endl;
            
            // cout<< "Rnode pkeys :";
            // for (int x = 0; x < rNode->parentNode->keys.size(); x++)
            //         cout<<rNode->parentNode->keys.at(x)<<endl;
                
            curNode->parentNode->children.push_back(rNode);
            //cout<< "ye hua?"<<endl;
            // for (int i = 0; i<curNode->parentNode->children.size();i++)
            //  cout<<get<0>(curNode->parentNode->children.at(i)->record.at(0))<<endl;

            sort(curNode->parentNode->children.begin(),curNode->parentNode->children.end(),childSort);
            curNode->parentNode->nNodes++;
        

                

            if (curNode->parentNode->keys.size() > order-1) {
                
                //cout<<"aa bhi raha hai idhar?     "<<curNode->parentNode->keys.size()<<endl;
                curNode->parentNode->nNodes--;
                // for (int i = 0; i< curNode->parentNode->keys.size(); i++)
                //     cout<<curNode->parentNode->keys.at(i)<<endl;
                splitNode(curNode->parentNode);
             }
            // else {
            //     cout<< "Poora nahi hua" << curNode->parentNode->keys.size() <<endl;
            // }
            
        }
    
    }
    else {                  //INTERNAL NODES 
        Node *rNode = new Node(false);
        //cout << "hello this is the internalnode style"<<endl;
        int x = order/2;
        //cout<< x << endl;
        //cout << curNode->keys.size() << endl;
        for (int i = curNode->keys.size()/2; i<curNode->keys.size(); i++)
            rNode->keys.push_back(curNode->keys.at(i));
        
        //int z = curNode->keys.size() - curNode->keys.size()/2;
        curNode->keys.erase(curNode->keys.begin() + curNode->keys.size()/2, curNode->keys.end());
        // cout << curNode->keys.size() << endl;
        // cout << rNode->keys.size() << endl;
        rNode->nNodes = rNode->record.size();
        curNode->nNodes = curNode->record.size();

        // DISTRIBUTING THE CHILDREN TOO
        if (curNode->children.size()%2) {
            for (int i = curNode->children.size()/2+1; i<curNode->children.size();i++) {
                rNode->children.push_back(curNode->children.at(i));
                curNode->children.at(i)->parentNode = rNode;
            }
                curNode->children.erase(curNode->children.begin() + curNode->children.size()/2 + 1, curNode->children.end());
            // cout<< "BACCHO KA SIZE KE BAAER ME BHI TOH SOCHO" <<endl;
            // cout << curNode->children.size() << endl;
            // cout << rNode->children.size() << endl;
        }
        else {
            for (int i = curNode->children.size()/2; i<curNode->children.size();i++) {
                rNode->children.push_back(curNode->children.at(i));
                curNode->children.at(i)->parentNode = rNode;
            }
            curNode->children.erase(curNode->children.begin() + curNode->children.size()/2, curNode->children.end());
            // cout<< "BACCHO KA PAPA KE BAAER ME BHI TOH SOCHO" <<endl;
            // cout << curNode->children.size() << endl;
            // cout << rNode->children.size() << endl;
        }
        //CHILDREN HAVE BEEN DISTRIBUTED

        if (curNode->parentNode == NULL) {
            Node *pNode = new Node(false);
            pNode->children.push_back(curNode);
            pNode->children.push_back(rNode);
            curNode->parentNode = pNode;
            rNode->parentNode = pNode;
            pNode->keys.push_back(rNode->keys.at(0));
            rNode->keys.erase(rNode->keys.begin());
            rNode->nNodes--;
            curNode->parentNode->nNodes++;
            //cout<< pNode->keys.at(0)<<endl;
            rootNode = pNode;
        }
        else {
            rNode->parentNode = curNode->parentNode;
            curNode->parentNode->keys.push_back(rNode->keys.at(0));
            rNode->keys.erase(rNode->keys.begin());
            sort(curNode->parentNode->keys.begin(),curNode->parentNode->keys.end());
            curNode->parentNode->children.push_back(rNode);
            curNode->parentNode->nNodes++;

            sort(curNode->parentNode->children.begin(),curNode->parentNode->children.end(),keySort);

           
            if (curNode->parentNode->keys.size()>order-1) {
                curNode->parentNode->nNodes--;
                splitNode(curNode->parentNode);
            }
        }
        
    
    }

}

void insertNode(Node *curNode, double k,string val) {
    if (curNode->isleaf) {
		//cout << "leaf root insert" << endl;
		
		curNode->record.push_back(make_tuple(k,val));
        sort(curNode->record.begin(),curNode->record.end());
		
        curNode->nNodes++;

        //for (int i = 0; i<curNode->record.size();i++) cout<<get<0>(curNode->record.at(i)) << " ";
		//cout << endl;

        if (curNode->record.size() > order-1) {
			//cout << "leaf split" << endl;			
            curNode->nNodes--;
            splitNode(curNode);
        }

		//cout << "leaf root had space" << endl;
    }
    else {
        int flag = 0;
        for (int i = 0; i<curNode->keys.size();i++) {
            if (k < curNode->keys.at(i)) {
                flag = 1;
                insertNode(curNode->children.at(i),k,val);
                break;
            }
        }
        if (flag == 0) {
            insertNode(curNode->children.at(curNode->children.size()-1),k,val);        
        }
        
        // sort(curNode->keys.begin(),curNode->keys.end());
        // if (curNode->keys.size()>order-1) {
        //     curNode->nNodes--;
        //     cout<<"Split karte hai bhai log";
        //     splitNode(curNode);
        
    }
    
}


void go(Node *curNode) {
    if (!curNode->isleaf) {
        go(curNode->children.at(0));
    }
    else {
        while (curNode!=NULL) {
            for (int i = 0; i<curNode->record.size();i++)
                cout << get<0>(curNode->record.at(i))<<endl;
            curNode = curNode->next;
        }
    }
}


void search(Node *curNode,double k,ofstream& o_file) {
    if (!curNode->isleaf) {
        int flag = 0;
        for (int i = 0; i<curNode->keys.size();i++) {
            if (k < curNode->keys.at(i)) {
                flag = 1;
                search(curNode->children.at(i),k,o_file);
                break;
            }
        }
        if (flag == 0) {
            search(curNode->children.at(curNode->children.size()-1),k,o_file);  
        }
    }
    else {
        //cout<<"I am a sahab tbh"<<curNode->record.size()<<endl;
        int found = 0;
        for (int i = 0 ;i<curNode->record.size();i++) {
            if (k == get<0>(curNode->record.at(i))) {
				o_file << get<1>(curNode->record.at(i));

				if(i+1 < curNode->record.size() && k != get<0>(curNode->record.at(i+1))){
					// single value in key
					 o_file << endl;
				}
				else if(i+1 < curNode->record.size() && k == get<0>(curNode->record.at(i+1))){
					// multiple values with same key
					while(i+1 < curNode->record.size() && k == get<0>(curNode->record.at(i+1))){
	                	o_file << "," << get<1>(curNode->record.at(++i));
					}
					o_file << endl;
				}				

    	        found = 1;
                break;
            }
        }
        if (found == 0)
        {
            o_file << "Null" <<endl;
        }            
    }
}

void search(Node *curNode,double k,double l,ofstream& o_file) {
    if (!curNode->isleaf) {
        int flag = 0;
        for (int i = 0; i<curNode->keys.size();i++) {
            if (k < curNode->keys.at(i)) {
                flag = 1;
                search(curNode->children.at(i),k,l,o_file);
                break;
            }
        }
        if (flag == 0) {
            search(curNode->children.at(curNode->children.size()-1),k,l,o_file);  
        }
    }
    else {
        int x = 0;

        for (int i = 0 ;i<curNode->record.size();i++) {
            if (k <= get<0>(curNode->record.at(i))) {
                x = i;
                break;
            }
        }  
  
        int found = 0;
        int flag = 0;

        while (flag == 0 && curNode != NULL) {
            for (int i = x ; i < curNode->record.size(); i++) {
                if (get<0>(curNode->record.at(i)) >= k && get<0>(curNode->record.at(i)) <= l) {
					if(found == 0)                    
						o_file << "(" <<get<0>(curNode->record.at(i))<<","<< get<1>(curNode->record.at(i))<< ")";
					else 
						o_file << ",(" <<get<0>(curNode->record.at(i))<<","<< get<1>(curNode->record.at(i))<< ")";
                    found = 1;
                }
                else {
                    flag = 1;
                    break;
                }    
            }

            curNode = curNode->next;
            x = 0;
        }
       
	    if (found == 0) {
            o_file << "Null" <<endl;
        }
		else o_file << endl;
    }
                   
}


int main(int argc, char *argv[]) {
    int z;
    ifstream file(argv[1]);

    if (file.fail()) {
        //cout<<"File not found";
        exit(1);
    }
    ofstream o_file("output_file.txt");

    string line;
    //PARSING THE INPUT
    
    while (getline(file, line)) {
        
        int i=0;
        int x=0;
        int y=0;
        double a=0;
        double b=0;
        string temp = "";
        string temp2 = "";

        if (isdigit(line[0])) {
      		istringstream buffer(line);
        	int value;
        	buffer >> value;
        	order = value;
        }

        if (line.substr(0,1)=="I")
        {
            if(line.substr(7,1)=="-")
            {
                for (i = 8;line.substr(i,1)!= ",";i++)
                {
                    x++;
                    
                }
                temp = line.substr(8,x);
                a = -stod(temp);
            }
            else {
                for (i = 7;line.substr(i,1)!= ",";i++)
                {
                    x++;
                }
                temp = line.substr(7,x);
                a = stod(temp);
            }
            
			y=i+1;
            x=0;
            
			for (i = y; line.substr(i,1)!=")";i++)
            {
                x++;
            }

            temp2 = line.substr(y,x);
			//cout << "inserting " << a << " "<< temp2 << " " <<endl; 
            insertNode(rootNode,a,temp2);
        }
        if (line.substr(0,1)=="S")
        {
            if(line.substr(7,1)=="-")
            {
                for (i = 8;line.substr(i,1)!= "," && line.substr(i,1)!=")";i++)
                {
                    x++;
                }
                temp = line.substr(8,x);
                a = -stod(temp);
            }
            else {
                for (i = 7;line.substr(i,1)!= "," && line.substr(i,1)!=")";i++)
                {
                    x++;
                }
                temp = line.substr(7,x);
                a = stod(temp);
            }

            if (line.substr(i,1)==",") {
                y=i+1;
                x=0;
                if (line.substr(y,1)=="-") {
                    y=y+1;
                    for (i = y; line.substr(i,1)!=")";i++)
                    {
                        x++;
                    }
                    temp2 = line.substr(y,x);
                    b = -stod(temp2);
                }
                else {
                    for (i = y; line.substr(i,1)!=")";i++)
                    {
                        x++;
                    }
                    temp2 = line.substr(y,x);
                    b = stod(temp2);
                }
				search(rootNode,a,b,o_file);
            }
            else {
				search(rootNode,a,o_file);
            }
        }
    }
    
    file.close();
    o_file.close();
    
	return 0;
}



