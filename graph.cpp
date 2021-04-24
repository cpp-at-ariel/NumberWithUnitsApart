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
        set<string> &_nodes(){
            return _nodes;
        }
        map<string, map<string, double>> &_graph(){
            return _graph;
        }
        graph(map<string, map<string, double>> graph, set<string> nodes):_graph(graph), _nodes(nodes){}
        void addNode(const string &_node){
            _nodes.insert(_node);
        }
        void addEdge(const string &src, const string &dst, double weight){
            addNode(src);addNode(dst);
            _graph[src][dst] = weight;
            _graph[dst][src] = 1/weight;
        }
        double getWeight(const string &src, const string &dst){
            return _graph[src][dst];
        }
        
        list<string> bfs(const string &src, const string &dest){
            if (0 == _nodes.count(dest) && _nodes.count(src) == 0){
                return list<string>{};
            }
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
                        visited.insert(dest);
                        return temp;
                    }if (visited.count(temp.front())==0){
                        temp.push_front(neighbor);
                        Queue.push(temp);
                    }                   
                }
            }
            return list<string>{};
        }  
};



