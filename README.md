# ImageProcessing

In this project some fundamental algorithms in mathematical morphology (a theory and technique for the analysis and processing of geometrical structures) are implemented along with a connected component labeling algorithm.

## Mathematical Topology 

* **Erosion** - The basic effect of the operator on a binary image is to erode away the boundaries of regions of foreground pixels (i.e. white pixels, typically). Thus areas of foreground pixels shrink in size, and holes within those areas become larger.

* **Dilation** - Exactly the opposite from Erosion. The main objective here is to gradually enlarge the boundaries of regions of foreground

* **Open** - The opening by reconstruction method is able to restore the objects completely after the erosion is applied. The main functionality is the same as the erosion's but it is less destructive on the original boundary shape. 

* **Close** - Exactly the opposite from Open. Closing is similar in some ways to dilation in that it tends to enlarge the boundaries of foreground (bright) regions in an image (and shrink background color holes in such regions), but it is less destructive of the original boundary shape.

#### Implementation
The user can apply the above filtering option with custom filter mask. He has the ability to choose between square,circle and diamonf filter mask with variable sizes. 

## Connected Components Labeling

Connected-component labeling (alternatively connected-component analysis, blob extraction, region labeling, blob discovery, or region extraction) is an algorithmic application of graph theory, where subsets of connected components are uniquely labeled based on a given heuristic.

Connected-component labeling is used in computer vision to detect connected regions in binary digital images. When integrated into an image recognition system or human-computer interaction interface, connected component labeling can operate on a variety of information. Blob extraction is generally performed on the resulting binary image from a thresholding step. Blobs may be counted, filtered, and tracked.

#### Implementation
The algoritm has ben implemented with the flood logic. This is recursive operation which traverses along the graph  until it reaches an edge (black background). Then it goes up one level and visit another naighbor until it finds another edge.


