#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include <queue>
#include <set>
#include <list>
#include <stack>
using namespace std;

class graph{
    protected:
        map<string, map<string, double>> _graph;
        set<string> _nodes;
        map<string,set<string>> _outEdges;

    public:
        set<string>& getMeNodes(){
            return _nodes;
        }
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
            if(_graph[src][dst] <= 0){
                return -1;
            }
            return _graph[src][dst];
        }

        void print(std::list<std::string> const &list)
        {
            for (auto const &i : list)
            {
                std::cout << i << " |-> ";
            }
            cout << endl;
        }

        double getConv(const string &src, const string &dst){
            stack<string> s;
            set<string> visited;
            map<string, double> con;
            s.push(src);
            con[src] = 1;
            while(!s.empty()){
                string cur = s.top();
                s.pop();
                if(visited.count(cur) < 1){
                    visited.insert(cur);
                    if (cur == dst){
                        return con[cur];
                    }
                    for (string str : _outEdges[cur])
                    {
                        if (visited.count(str) < 1)
                        {
                            con[str] = getWeight(cur, str) * con[cur];
                            s.push(str);
                        }
                    }
                }
            }
            return -1;
        }
};



