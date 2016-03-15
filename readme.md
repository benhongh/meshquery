#MeshQuery
This is a coding practice to demonstrate how to locate 
the closest point of a 3D mesh in relation to a given
reference point.

##Assumptions
2D mesh is boring and higher dimensions beyond 3 give me real 
headache. For all pratical purposes this demo assumes a 3D mesh.

Each mesh is a collection of **triangular faces** with no normal
vector associated with any vertices (i.e. a mesh is a faceted 
geometry).

In the rare cases where multiple closest points exist on the mesh
from the given reference point, only **one** of such closest points
shall be computed.

If the 3D mesh forms an enclosure and the reference point happens
to be inside the mesh, this demo shall locate the closest point on
the **internal** surface of the manifold. Collision detection is
way too complicated for a 3-hour exercise.

##Solution

##Closest vertex
The first step is to short list a number of faces where the closest
point may be found. I am willing to gamble on that the face(s) where
the closest point is on also has the vertex that is closest to the
reference point.

To find the closest vertex we first construct a virtual cube that 
centres on the given reference point. The virtual cube shall have 
a size of twice the max distance on each of its edges. Any vertex
from the mesh that isn't inside this box is automatically rejected.
Since this step does not involve multiplication it should be 
computationally efficient.

For each of the vertices inside the virtual box, we measure the 
squre of its distance to the reference point, and thus locate the
vertex with minimum measurement. By measuring the square of the
vertices' distance we avoid the unnecessary square root computation.

##Faces
Once the closest vertex is found, we then obtain all faces from the
mesh that share this vertex. The closest point may be located:

* on one of the faces if the point's normal projection falls within 
  the triangle
* on one of the edges if the point's edge projection falls within
  the edge
* on the vertex we have just found

##Edge projection
Given an edge with ends located at *v1* and *v2* (both are vectors) and
a reference point *R*, the edge projection is 

    p1 = v1 + dot(R-v1, n) * n  where n = unit(v2-v1)

This is only valid if the dot product is between 0 and |v2-v1|, in
which case the projection lies within the edge.

The projection distance to the edge can be obtained by:

    d_edge = |R - p1|

##Face projection
If the reference point *R* has valid edge projections on all three
edges of the same face, then we might be able to find an even
closer point by doing a face projection. We don't really need to
compute the project point per se because we have already
established that the projection is inside the face. All it's left
to do is to calculate the projection distance.

Given a triangular face with vertices *v1*, *v2*, and *v3*,
we can obtain the normal vector *n*:

    nr = cross(unit(v3-v1), unit(v2-v1))
    
the order (clockwise or counter-clockwise) of the vertices should
not matter as we conveniently took a concession that internal
distance is also valid. See what I did there to save my time :-)

The projection distance, finally, can be obtained by projecting 
the relative vector to the normal vector:

    d_face = |dot(nr, R-v1)|
    
##Final selection
Given the obvious geometric relationship that

    d_face <= d_edge <= d_vertex

and given that the number of faces sharing the same vertex is
most likely to be small in number (unless it is a very contrived
mesh), for this part we just use brute force.

Round 1 of the selection process picks the shortest *d_face*.

Round 2 picks the shortest *d_edge*.

If no point is yielded, we simply return the selected vertex back
in step 1.

#Dependencies
Implementing basic linear algebra can be time consuming so for this
demo the Eigen library (MPL2 licensed) is used. This particular
library was chosen because:

* It came top on my Google search
* It also implements SIMD

#Threading
This is a single-threaded demo given the highly limited time
constraint. But for discussion's sake let's just say that some
degree of parallelism can potentially be used improve the query
performance if (and it is a big if) the mesh is incredibly 
complex.
