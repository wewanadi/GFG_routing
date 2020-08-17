## Greedy Face Greedy Routing
###### tags:`Face Routing` `Greedy Face Greedy Routing` `GFG Routing`

---
## Main Idea
### Greedy Routing
- Only Greedy will suffer deadend, than never get to destination.
<img src=https://github.com/wewanadi/GFG_routing/blob/master/.picture/GFG%20(2).png width="600">

---
### Face Routing
- If we can walk every steps face by face, than greedily choose face. 
- However, we can't walk on face,we can only walk along the edge.
<img src=https://github.com/wewanadi/GFG_routing/blob/master/.picture/GFG%20(3).png width="600">

- bad case for Face Routing
<img src=https://github.com/wewanadi/GFG_routing/blob/master/.picture/GFG%20(5).png width="600">

---
### GFG Routing
- Walking on face, sometimes seems taking a long route.
- What if we Greedy walk until deadend, than convert to face routing mode.
- Until there is no deadend existed, convert back to greedy mode.
<img src=https://github.com/wewanadi/GFG_routing/blob/master/.picture/GFG%20(4).png width="600">

---

## Algorithm

### How to walk on a face


### Algorithm
- Get a graph
- Generate some links, to make it a planar subgraph.
- Do face routing alg.
