#include "face_routing.h"
#define NOTUSING -4

class Pack : public Package   {
    public :
        struct coordinate deadend;
};

class GFG : public FR {
    friend void run_gfg(int source, int distination, std::vector<class GFG> &node); 
public:
    GFG(struct coordinate tr2) : FR(tr2) {}
        //the first function calls GFG_check -> so it starts on gfg
        void check() {
            while (package_queue.size()!=0) {
                //printf("((%d))\n", location.id);
                Package package = package_queue.front();
                package_queue.pop();
                if (package.next_hop == location.id) 
                    getnexthop(package);
            }
        }
        //the diffrent of gfg and fr
        void getnexthop(Package package) {
            //printf("%d %d\n", location.id, package.distination.id);
            if (location.id == package.distination.id) {
                package.path.push(location.id);
                print_flow(package);
                return;
            }
            if (!greedy_routing(package))
                face_routing(package);
        }

        bool greedy_routing(Package &package)     {
            struct coordinate closest = greedy_closest(package);
            if ((closest ^ package.distination) > (location ^ package.distination) && package.deadend.id == NOTUSING) {
                    package.deadend = location;
                    return false;
            }
            else if ((closest ^ package.distination) < (package.deadend ^ package.distination)) {
                    package.next_hop = closest.id;
                    package.last_hop = location.id;
                    package.diraction = package.distination ->* closest;
                    package.path.push(location.id);
                    package.deadend.id = NOTUSING;
                    send_queue.push(package);
                    printf("[G]%d\n", package.next_hop );
                    return true;
                }
            else
                return false;
        }

        //find the nearest_nb to the distination
        struct coordinate greedy_closest (Package package)    {
            struct coordinate min = nearby_node[0];
            for (int i = 1; i < nearby_node.size();i++)
                if ((min ^ package.distination) > (nearby_node[i] ^ package.distination))
                    min = nearby_node[i];
            return min ;
        }

        //odd face routing
        void face_routing(Package package)  {
            int min_node;
            double angle,min_angle=361;
            for (int i = 0; i < cutoff_node.size(); i++) {
                angle = package.diraction.right_hand_angle(location->*cutoff_node[i]);
                if (angle <0.00001) angle =360;
                //printf("\n![%d,%d](%lf,%lf)   [(%d,%d) , %lf]", package.last_hop, location.id,package.diraction.x,package.diraction.y,package.next_hop, cutoff_node[i].id, angle);
                if ( angle < min_angle ) {
                    min_angle = angle;
                    min_node = i;   
                }
            }
            //printf("\t\t%d\n", between(package.distination, package.intersection, location, cutoff_node[min_node]));
            if ( between(package.distination,package.intersection,location,cutoff_node[min_node]) ) {
                package.intersection = get_inte(package.distination, package.intersection, location, cutoff_node[min_node]);
                package.diraction = package.intersection ->* location;
                if (package.diraction.outer_product(package.intersection ->* package.source)!=1) {
                face_routing(package);
                return;
                }
            }
            package.next_hop = cutoff_node[min_node].id;
            package.last_hop = location.id;
            package.diraction = location ->* cutoff_node[min_node];
            package.path.push(location.id);
            send_queue.push(package);
            printf("[F]%d\n", package.next_hop);
        }

        void make_package (struct coordinate distination) {
            Package package;
            package.source = location;
            package.distination = distination;
            package.intersection = location;
            package.last_hop = distination.id;
            package.next_hop = location.id;
            package.deadend.id = NOTUSING;
            package.deadend.x = __DBL_MAX__;
            package.deadend.y = __DBL_MAX__;
            package.diraction = distination ->* location;

            for (int i = 0; i < cutoff_node.size(); i++) 
                if (distination.id == cutoff_node[i].id)    {
                    package.path.push(location.id);
                    package.last_hop = location.id;
                    package.next_hop = distination.id;
                    package.diraction = location->* distination;
                    send_queue.push(package);
                    return;
                }
            receive(package);
        }
        

};

void run_gfg (int source,int distination,std::vector<class GFG> &node) {
    node[source].make_package(node[distination].info());
    int n = 200;
    while (n--) {
    for (int i = 0; i < node.size(); i++)   
        node[i].check();
   
    for (int i = 0; i < node.size(); i++)
            while (node[i].send_queue.size()!=0) {
                Package package = node[i].send_queue.front();
                node[i].send_queue.pop();
                for (int j = 0; j < node[i].nearby_node.size(); j++)    {
                    int now = node[i].nearby_node[j].id;
                    node[now].receive(package);
                }
        }
    }
        printf("\n");
}