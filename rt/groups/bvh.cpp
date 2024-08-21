#include <rt/groups/bvh.h>

namespace rt {

BVH::BVH()
{
    Node* node = new Node;
    root = node;
}

void BVH::rebuildIndex() {
    Point mi(FLT_MAX, FLT_MAX, FLT_MAX);
    Point ma(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    for (Primitive* p : primitives)
    {
        mi = min(p->getBounds().min, mi);
        ma = max(p->getBounds().max, ma);
    }
    boundingBox = BBox(mi, ma);

    Primitives prims = primitives;          // all primitives
    split(root, &boundingBox, prims, 0, 0);         // start the recursive building process of the tree structure
                                            // with root node start bounding box and all primitives
    //std::cout << "max leaf size = " << maxLeafSize << std::endl;
}

// TODO: Primitives always copy !
void BVH::split(Node* parent, BBox* bbox, Primitives prims, int noChange, int axisOffset) {
    this->maxSplits--;
    // TERMINATION CONDITION CHECK
    if ((prims.size() < 3) || (noChange > 50) /*|| (maxSplits == 0)*/) {  // termination when primitives less than 3 or 
                                                 // primitives didnt change the last ?-steps
                                                 // WE ARE NOW IN A LEAF
        maxLeafSize = maxLeafSize > prims.size() ? maxLeafSize : prims.size();
        parent->isLeaf = true;
        parent->left = nullptr;
        parent->right = nullptr;
        //parent->location = 0;       // not neccesary
        //parent->splitAxis = -1;
        parent->box = *bbox;
        // Setting the primitives
        parent->primitives = prims;
        return;
    }
    // WE ACTUALLY WANT TO SPLIT

    // SPLITTING LOCATION
    float globalSplitPoint;

    Vector axisLength = bbox->max - bbox->min;              // x => length of x Axis, y => length of y axis, z => length of z axis
    int splitAxis = axisLength.maxComp();

    if (axisOffset == 0) {
        float localSplitPoint = axisLength[splitAxis] / 2;
        globalSplitPoint = bbox->min[splitAxis] + localSplitPoint;
    }
    else if (axisOffset == 1) {
        axisLength[splitAxis] = -FLT_MAX;
        splitAxis = axisLength.maxComp();
        float localSplitPoint = axisLength[splitAxis] / 2;
        globalSplitPoint = bbox->min[splitAxis] + localSplitPoint;
    }
    else if (axisOffset == 2) {
        splitAxis = axisLength.minComp();
        float localSplitPoint = axisLength[splitAxis] / 2;
        globalSplitPoint = bbox->min[splitAxis] + localSplitPoint;
    }
    else {
        float localSplitPoint = axisLength[splitAxis] / 2;
        globalSplitPoint = bbox->min[splitAxis] + localSplitPoint;
    }

    // SPLIT THE PRIMITIVES 
    Primitives lPrims;
    Primitives rPrims;

    BBox rbbox = BBox::empty();   // calculate right bounding box
    BBox lbbox = BBox::empty();   // calculate left bounding box

    for (Primitive* p : prims) {
        BBox bbox_ = p->getBounds();
        if (center(&bbox_, splitAxis) < globalSplitPoint) {       // sort in left tree
            lPrims.push_back(p);
            lbbox.extend(bbox_);                             // create new bounding box of left side
        }
        else {                                              // sort in right tree
            rPrims.push_back(p);
            rbbox.extend(bbox_);                             // create new bounding box of right side
        }
    }
    // NOTE: clear old primitives vector ?

    // CHECK IF ONE SIDE IS EMPTY
    if (lPrims.empty()) {                                   // left side is empty
        if (axisOffset < 2) {
            noChange++;
            axisOffset++;
            split(parent, &rbbox, rPrims, noChange, axisOffset);
        }
        else if (!fallback) {
            noChange++;
            split(parent, &rbbox, rPrims, noChange, axisOffset);
        }
        else {
            lPrims.push_back(rPrims.back());
            rPrims.pop_back();
            lPrims.push_back(rPrims.back());
            rPrims.pop_back();
            // build new bounding boxes
            for (Primitive* p : lPrims) {
                lbbox = BBox::empty();
                lbbox.extend(p->getBounds());
            }
            for (Primitive* p : rPrims) {
                rbbox = BBox::empty();
                rbbox.extend(p->getBounds());
            }
        }
    }
    else if (rPrims.empty()) {                              // right side is empty
        if (axisOffset < 2) {
            noChange++;
            axisOffset++;
            split(parent, &lbbox, lPrims, noChange, axisOffset);
        }
        else if (!fallback) {
            noChange++;
            split(parent, &lbbox, lPrims, noChange, axisOffset);
        }
        else {
            rPrims.push_back(lPrims.back());
            lPrims.pop_back();
            rPrims.push_back(lPrims.back());
            lPrims.pop_back();
            // build new bounding boxes
            for (Primitive* p : lPrims) {
                lbbox = BBox::empty();
                lbbox.extend(p->getBounds());
            }
            for (Primitive* p : rPrims) {
                rbbox = BBox::empty();
                rbbox.extend(p->getBounds());
            }
        }
    }
    else {                                                  // both sides are !empty continue with split
        Node* left = new Node;                  // create new child nodes
        Node* right = new Node;

        parent->left = left;         // setting the node as child nodes in the parent
        parent->right = right;
        parent->box = *bbox;
        //parent->splitAxis = splitAxis;        // set the attributes of parent node
        //parent->location = globalSplitPoint;
        parent->isLeaf = false;

        // SPLITTING
        split(left, &lbbox, lPrims, 0, 0);
        split(right, &rbbox, rPrims, 0, 0);
    }
}

BBox BVH::getBounds() const {
    return boundingBox;         // precalculated in rebuildIndex() !
}



Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const {
    Intersection intersection = Intersection::failure();        
    std::pair<float, float> i = boundingBox.intersect(ray);    
    if (i.first > i.second) return Intersection::failure();     
    
    std::stack<BVH::Node*> nodeStack;                            
    const Node* currentNode = root;

    while (true) {
        while (!currentNode->isLeaf) {
            
            std::pair<float, float> t_l = currentNode->left->box.intersect(ray);
            std::pair<float, float> t_r = currentNode->right->box.intersect(ray);
            
            bool left_intersection = t_l.first < t_l.second;
            bool right_intersection = t_r.first < t_r.second;

            if (left_intersection && !right_intersection) { 
                currentNode = currentNode->left;
            }
            else if (!left_intersection && right_intersection) {
                currentNode = currentNode->right;
            }
            else if (left_intersection && right_intersection) {
                nodeStack.push(currentNode->right);
                currentNode = currentNode->left;
            }
            else {
                break;
            }
        }

        for (Primitive* p : currentNode->primitives)
        {
            Intersection curr = p->intersect(ray, previousBestDistance);
            if (curr) {
                if (curr.distance < previousBestDistance) {
                    intersection = curr;
                    previousBestDistance = curr.distance;
                }
            }
        }

        if (nodeStack.empty()) {
            break;
        }
        else {
            currentNode = nodeStack.top();
            nodeStack.pop();
        }
    }

    return intersection;
}

float BVH::center(BBox* bbox, int axis) {
    float local = (bbox->max[axis] - bbox->min[axis]) / 2;
    float global = bbox->min[axis] + local;
    return global;
}

void BVH::add(Primitive* p) {
    primitives.push_back(p);
}

void BVH::setMaterial(Material* m) {
    for (Primitive* p : primitives) {
        p->setMaterial(m);
    }
}

void BVH::setCoordMapper(CoordMapper* cm) {
    for (Primitive* p : primitives) {
        p->setCoordMapper(cm);
    }
}

void BVH::serialize(BVH::Output& output) {
    // To implement this function:
    // - Call output.setNodeCount() with the number of nodes in the BVH
    /* TODO */
    // - Set the root node index using output.setRootId()
    /* TODO */
    // - Write each and every one of the BVH nodes to the output using output.writeNode()
    /* TODO */ NOT_IMPLEMENTED;
}
void BVH::deserialize(BVH::Input& input) {
    // To implement this function:
    // - Allocate and initialize input.getNodeCount() nodes
    /* TODO */
    // - Fill your nodes with input.readNode(index)
    /* TODO */
    // - Use the node at index input.getRootId() as the root node
    /* TODO */ NOT_IMPLEMENTED;
}

}