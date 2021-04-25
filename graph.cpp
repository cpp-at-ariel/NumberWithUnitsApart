#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include <queue>
#include <set>
#include <list>
using namespace std;

class graph{
    protected:
        map<string, map<string, double>> _graph;
        set<string> _nodes;
        map<string,set<string>> _outEdges;

    public:
        // set<string> &_nodes(){
        //     return _nodes;
        // }
        // map<string, map<string, double>> &_graph(){
        //     return _graph;
        // }
        // map<string,set<string>> &_outEdges(){
        //     return _outEdges;
        // }
        void addOut(const string &src, const string &dst){
            if (_outEdges.count(src) > 0)
            {
                _outEdges[src].insert(dst);
            }else{
                set<string> temp{dst};
                _outEdges[src] = temp;
            }
        }
        void addNode(const string &_node){
            _nodes.insert(_node);
        }
        void addEdge(const string &src, const string &dst, double weight){
            addNode(src);addNode(dst);
            _graph[src][dst] = weight;
            _graph[dst][src] = ((double)1)/weight;
            addOut(src,dst);
            addOut(dst,src);
        }
        double getWeight(const string &src, const string &dst){
            return _graph[src][dst];
        }
        
        list<string> bfs(const string &src, const string &dest){
            set<string> visited;
            queue<list<string>> Queue;

            list<string> l;
            l.push_front(src);
            Queue.push(l);

            while (!Queue.empty())
            {
                list<string> temp = Queue.front();
                visited.insert(temp.front());
                Queue.pop();
                for(string neighbor : _outEdges[temp.front()]){
                    if (neighbor == dest){
                        //probaly not needed
                        visited.insert(dest);
                        //i added
                        temp.push_front(dest);
                        //************
                        return temp;
                    }if (visited.count(temp.front())==0){
                        temp.push_front(neighbor);
                        Queue.push(temp);
                    }                   
                }
            }
            return list<string>{};
        }  
        double ThereIsPath(const string &src, const string &dest){
            if (0 == _nodes.count(dest) && _nodes.count(src) == 0){
                cout << "There is a measure unit not that is not in src file" << endl;
                return -1;
            }
            list<string> bfsReturn = bfs(src,dest);
            if(bfsReturn.empty()){
                cout << "Can't convert this 2.." << endl;
                return -1;
            }

            //The last in the list is src and the first is the destenation
            //we need to get weights and multiply them until we reach the end.
            string temp = bfsReturn.back();
            bfsReturn.pop_back();
            
            string temp2;
            double returnVal = 1.0;
            while (!bfsReturn.empty())
            {
                temp2 = bfsReturn.back();
                bfsReturn.pop_back();
                returnVal *= getWeight(temp,temp2);
                // cout << "retval: " <<returnVal << endl;
                temp = temp2;
            }
            return returnVal;          
        }
};



