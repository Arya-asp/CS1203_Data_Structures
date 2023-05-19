#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


// Define a structure to represent a 2D point
typedef struct {
    double x;
    double y;
} Point;

// Structure for a node in the kd-tree (quadtree)
typedef struct kdNode {
    Point point;
    // The left and right pointers are used to represent the left and right subtrees
    // left and right are the same as up and down in a quadtree depending on the level (which determines the dimension of the split) 
    struct kdNode* left; 
    struct kdNode* right;
} KDNode;

// Function to calculate the Euclidean distance between two points
double distance(Point p1, Point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

// Function to create a new kd-tree node
KDNode* createKDNode(Point point) {
    KDNode* newNode = (KDNode*)malloc(sizeof(KDNode));
    newNode->point = point;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a point into the kd-tree
KDNode* insertKDNode(KDNode* root, Point point, int level) {
    // If the tree is empty, create a new node as the root
    if (root == NULL) {
        return createKDNode(point);
    }

    // Calculate the current dimension (x or y) for splitting
    int cd = level % 2;

    // Recursively insert the point in the left or right subtree
    if (cd == 0) {
        if (point.x < root->point.x) {
            root->left = insertKDNode(root->left, point, level + 1);
        } else {
            root->right = insertKDNode(root->right, point, level + 1);
        }
    } else {
        if (point.y < root->point.y) {
            root->left = insertKDNode(root->left, point, level + 1);
        } else {
            root->right = insertKDNode(root->right, point, level + 1);
        }
    }

    return root;
}

// Function to perform nearest neighbor search using linear search
Point linearSearch(Point* points, int numPoints, Point query) {
    double minDistance = distance(points[0], query);
    Point nearestNeighbor = points[0];

    for (int i = 1; i < numPoints; i++) {
        double currDistance = distance(points[i], query);
        if (currDistance < minDistance) {
            minDistance = currDistance;
            nearestNeighbor = points[i];
        }
    }

    return nearestNeighbor;
}

// Function to perform nearest neighbor search using kd-tree
Point nearestNeighborSearchKD(KDNode* root, Point query, int level) {
    if (root == NULL) {
        Point emptyPoint = {0, 0};
        return emptyPoint;
    }

    // Calculate the current dimension (x or y) for splitting
    int cd = level % 2;

    KDNode* nextBranch;
    KDNode* oppositeBranch;

    if (cd == 0) {
        if (query.x < root->point.x) {
            nextBranch = root->left;
            oppositeBranch = root->right;
        } else {
            nextBranch = root->right;
            oppositeBranch = root->left;
        }
    } else {
        if (query.y < root->point.y) {
            nextBranch = root->left;
            oppositeBranch = root->right;
        } else {
            nextBranch = root->right;
            oppositeBranch = root->left;
        }
    }

    // Recursively search in the next branch
    Point best = nearestNeighborSearchKD(nextBranch, query, level + 1);

    // Check if the current node is closer than the best found so far
    if (distance(root->point, query) < distance(best, query)) {
        best = root->point;
    }

    // Check if there is any chance of a closer point in the opposite branch
    if (distance(query, best) > fabs(cd == 0 ? query.x - root->point.x : query.y - root->point.y)) {
        Point alternative = nearestNeighborSearchKD(oppositeBranch, query, level + 1);
        if (distance(query, best) > distance(alternative, query)) {
            best = alternative;
        }
    }

    return best;
}

int main() {
    // Define the initial number of points and the number of steps
    int initialNumPoints = 1;
    int numSteps = 7; // 1, 10, 100, 1000, 10000, 100000, 1000000

    printf("Performance Comparison:\n\n");
    printf("Number of Points\tLinear Search Time (seconds)\tKD-Tree Search Time (seconds)\n");

    int numPoints = initialNumPoints;
    for (int step = 1; step <= numSteps; step++) {
        // Generate random points for testing
        Point* points = (Point*)malloc(numPoints * sizeof(Point));
        for (int i = 0; i < numPoints; i++) {
            points[i].x = (double)rand() / RAND_MAX;
            points[i].y = (double)rand() / RAND_MAX;
        }

        // Create a query point
        Point query = {0.25, 0.25};

        // Perform nearest neighbor search using linear search and measure execution time
        clock_t linearStartTime = clock();
        Point nearestNeighborLinear = linearSearch(points, numPoints, query);
        clock_t linearEndTime = clock();
        double linearTime = (double)(linearEndTime - linearStartTime) / CLOCKS_PER_SEC;

        // Build the kd-tree
        KDNode* kdTreeRoot = NULL;
        for (int i = 0; i < numPoints; i++) {
            kdTreeRoot = insertKDNode(kdTreeRoot, points[i], 0);
        }

        // Perform nearest neighbor search using kd-tree and measure execution time
        clock_t kdSearchStartTime = clock();
        Point nearestNeighborKD = nearestNeighborSearchKD(kdTreeRoot, query, 0);
        clock_t kdSearchEndTime = clock();
        double kdSearchTime = (double)(kdSearchEndTime - kdSearchStartTime) / CLOCKS_PER_SEC;

        // Print the results
        printf("%d\t\t\t\t%f\t\t\t\t%f\n", numPoints, linearTime, kdSearchTime);

        // Increase the number of points for the next step
        numPoints *= 10;
    }

    return 0;
}