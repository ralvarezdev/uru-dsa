#include <algorithm>
#include <sstream>
#include <random>
#include <iostream>

#include "../../../../submodules/udemy-dsa-cpp/data-structures/undirected-graphs/base.h"
#include "../../../../submodules/udemy-dsa-cpp/data-structures/single-linked-lists/number.h"
#include "../terminal/ansiEsc.h"
#include "../namespaces.h"

using std::cout;
using std::fill;
using std::ostringstream;
using std::random_device;
using std::uniform_int_distribution;

#ifndef DUNGEONS
#define DUNGEONS

// Initialize Seed
random_device rd;

// DUNGEON ROOM CLASS

class DungeonRoom
{
private:
  bool hasKey;
  bool isEntrance;
  bool isExit;

public:
  // Constructors
  DungeonRoom(bool, bool, bool);

  // Public Methods
  bool getHasKey() { return hasKey; };
  bool getIsEntrance() { return isEntrance; };
  bool getIsExit() { return isExit; };
};

// DungeonRoomPtr Definition
using DungeonRoomPtr = DungeonRoom *;

// DUNGEONS GRAPH CLASS

class DungeonsGraph : public UndirGraph<DungeonRoomPtr>
{
public:
  // Inherit Constructors
  using UndirGraph<DungeonRoomPtr>::UndirGraph;

  // Destructor
  virtual ~DungeonsGraph()
  {
    UndirNodePtr<DungeonRoomPtr> node;
    DungeonRoomPtr data;

    // Deallocate Node's Data
    for (int nodesLength = this->nodes->getLength(); nodesLength > 0; nodesLength--)
    {
      node = this->nodes->remove();
      data = node->getData();

      delete data, node;
    }
  }
};

// DungeonsGraphPtr Definition
using DungeonsGraphPtr = DungeonsGraph *;

// DUNGEONS CLASS

class Dungeons
{
private:
  // Dungeon Levels
  DungeonsGraphPtr level1 = NULL;
  DungeonsGraphPtr level2 = NULL;
  DungeonsGraphPtr level3 = NULL;
  int numberRooms[dungeons::nLevels] = {dungeons::level1Rooms, dungeons::level2Rooms, dungeons::level3Rooms};

  // Nodes and Edges
  NumberSingleLinkedList<int> **nodesIds = NULL;
  SingleLinkedList<Edges> **roomsConns = NULL;
  int **specialRooms = NULL;

  // Dungeon-related Information
  ostringstream *dungeonsInfo = NULL;

  // Private Methods
  SingleLinkedList<int> *getShortestPath(int, int, int);
  void getSpecialRooms();
  QueueLinkedList<int> **getDungeonRoomsIndexes();
  QueueLinkedList<DungeonRoomPtr> **getDungeonRooms();
  void getDungeonRoomsConns();
  int getNodeId(int nodeIndex) { return nodeIndex + dungeons::firstNodeId; };
  int getNodeIndex(int nodeId) { return nodeId - dungeons::firstNodeId; };

  void swapIntArray(int *array, int swapFromIndex, int swapToIndex = 0, int valueFromIndex = dungeons::unasigned);
  void pushEdge(SingleLinkedList<Edge> **, int, int, int, int);
  void removePossibleEdge(int **edges, int *edgesCounter, int **edgesIndexes, int srcNodeIdIndex, int toNodeIdIndex = 0);

public:
  // Constructors
  Dungeons();

  // Destructor
  virtual ~Dungeons()
  {
    // Deallocate Memory
    delete level1, level2, level3, dungeonsInfo;

    for (int i = 0; i < dungeons::nLevels; i++)
    {
      // Deallocate Dungeon Special Rooms Nodes ID
      delete[] specialRooms[i];

      // Deallocate Dungeon Rooms Nodes and Edges
      delete nodesIds[i], roomsConns[i];
    }
    delete[] specialRooms;
  }

  // Public Methods
  // void playGame();
  void printDungeonsInfo() { cout << this->dungeonsInfo->str(); };
};

// DUNGEON ROOM CLASS

// Dungeon Room Class Constructors
DungeonRoom::DungeonRoom(bool hasKey, bool isEntrance, bool isExit)
{
  this->hasKey = hasKey;
  this->isEntrance = isEntrance;
  this->isExit = isExit;
}

// DUNGEON CLASS

// Dungeon Class Constructors
Dungeons::Dungeons()
{
  UndirGraphPtr<DungeonRoomPtr> *dungeonLevels;
  QueueLinkedList<DungeonRoomPtr> **dungeonsRooms;

  // Initialize Dungeons Graphs for Each Level
  this->level1 = new DungeonsGraph(dungeons::firstNodeId);
  this->level2 = new DungeonsGraph(dungeons::firstNodeId);
  this->level3 = new DungeonsGraph(dungeons::firstNodeId);

  dungeonLevels = new UndirGraphPtr<DungeonRoomPtr>[dungeons::nLevels]
  { this->level1, this->level2, this->level3 };

  // Intialize Dungeon Nodes IDs, Rooms Connections, Special Rooms, Among Others Dynamic Arrays
  this->nodesIds = new NumberSingleLinkedList<int> *[dungeons::nLevels];
  this->roomsConns = new SingleLinkedList<Edges> *[dungeons::nLevels];
  this->specialRooms = new int *[dungeons::nLevels];

  // Initialize the Required Data Structures
  for (int i = 0; i < 3; i++)
  {
    this->nodesIds[i] = new NumberSingleLinkedList<int>(dungeons::unasigned);
    this->roomsConns[i] = new SingleLinkedList<Edges>(NULL);
    this->specialRooms[i] = new int[dungeons::nLevels];
  }

  // Initialize Dungeons Information Stream
  this->dungeonsInfo = new ostringstream;

  // Get Key, Entrance and Exit Room Index
  this->getSpecialRooms();

  // Get Random Dungeon Rooms Index
  dungeonsRooms = this->getDungeonRooms();

  // Add Dungeon Rooms to its Given Graph
  for (int i = 0; i < dungeons::nLevels; i++)
    this->nodesIds[i] = dungeonLevels[i]->addNodes(dungeonsRooms[i]);

  // Get Random Dungeon Rooms Connections
  this->getDungeonRoomsConns();

  // Add Dungeon Rooms Connections to its Given Graph
  for (int i = 0; i < dungeons::nLevels; i++)
    dungeonLevels[i]->addEdges(this->roomsConns[i]);

  // Print Dungeons Levels
  if (setup::debugMode)
  {
    int key, entrance, exit, nRooms, shortestKeyLength, shortestExitLength, totalPathLength, nodeId;
    Edge edge;
    Edges nodeEdges;
    QueueLinkedList<Edge> *edges;
    SingleLinkedList<int> *shortestKey, *shortestExit, *currPath;
    ostringstream *dungeonsInfo;

    dungeonsInfo = this->dungeonsInfo;

    // Save Dungeons Info
    for (int i = 0; i < dungeons::nLevels; i++)
    {
      // Get Dungeon Data
      key = this->specialRooms[i][dungeons::keyIndex];
      entrance = this->specialRooms[i][dungeons::entranceIndex];
      exit = this->specialRooms[i][dungeons::exitIndex];
      nRooms = this->numberRooms[i];

      // Add Dungeon Level General Data to Stream
      *dungeonsInfo << "Level [" << i + 1 << "]\n"
                    << "Key Room: " << key << '\n'
                    << "Entrance Room: " << entrance << '\n'
                    << "Exit Room: " << exit << '\n'
                    << "Total Rooms: " << nRooms << '\n'
                    << "Rooms Connections: ";

      // Add Dungeon Level Rooms Connections Data to Stream
      for (int roomsLength = this->roomsConns[i]->getLength(); roomsLength > 0; roomsLength--)
      {
        // Get First Node Edges and Push it Back
        nodeEdges = this->roomsConns[i]->removeBack();

        // Get Edges for the Given Source Node ID
        edges = nodeEdges->getEdges();

        for (int edgesLength = edges->getLength(); edgesLength > 0; edgesLength--)
        {
          // Get First Edge and Push it Back
          edge = edges->dequeue();

          // Add Node Edge Data to Stream
          *dungeonsInfo << nodeEdges->getSrcId()
                        << " -> "
                        << edge->getDstId()
                        << " [" << edge->getWeight() << ']';

          if (!(edgesLength == 1 && roomsLength == 1))
            *dungeonsInfo << ", ";

          // Deallocate Memory
          delete edge;
        }
      }

      // Add Dungeon Level Shortest Paths
      *dungeonsInfo << "\nShortest Path: ";
      shortestKey = this->getShortestPath(i, entrance, key);
      shortestExit = this->getShortestPath(i, key, exit);

      // Remove Repeated Node
      shortestExit->remove();

      shortestKeyLength = shortestKey->getLength();
      shortestExitLength = shortestExit->getLength();
      totalPathLength = shortestKeyLength + shortestExitLength;

      // Add Dungeon Level Shortest Paths Data to Stream
      bool firstData = true;
      for (; totalPathLength > 0; totalPathLength--)
      {
        currPath = (totalPathLength > shortestExitLength) ? shortestKey : shortestExit;

        // Get First Node ID
        nodeId = currPath->remove();

        // Add Node ID to Stream
        if (!firstData)
          *dungeonsInfo << " -> ";

        else
          firstData = false;

        *dungeonsInfo << nodeId;
      }
      *dungeonsInfo << "\n\n";
    }

    // Deallocate Memory
    delete edges, shortestKey, shortestExit;
  }

  // Deallocate Memory
  delete[] dungeonLevels;
}

// Method to Get the Distribution Results of the Special Rooms for Each Level
void Dungeons::getSpecialRooms()
{
  int *levelRooms, nRooms, index, n;

  for (int i = 0; i < dungeons::nLevels; i++)
  {
    nRooms = this->numberRooms[i];

    // Initialize the Required Data Structures
    levelRooms = new int[nRooms];

    // Fill Level Rooms
    for (int j = 0; j < nRooms; j++)
      levelRooms[j] = j;

    // Get Key, Entrance and Exit Room ID
    for (int j = 0; j < dungeons::nSpecialRooms; j++)
    {
      // Create Random Distribution
      n = nRooms - 1 - j;
      uniform_int_distribution<int> distLevel(0, n);

      // Get Random Index
      index = distLevel(rd);

      // Store Random Index
      this->specialRooms[i][j] = levelRooms[index];

      // Remove the Possibility to Get the Given Index Again
      this->swapIntArray(levelRooms, n, index);
    }

    // Deallocate Memory
    delete[] levelRooms;
  }
}

// Method to Get the Dungeon Rooms Indexes for Each Level
QueueLinkedList<int> **Dungeons::getDungeonRoomsIndexes()
{
  int nRooms, *levelRooms, index, n;

  // Initialize Dungeon Rooms Indexes Queue Dynamic Array
  QueueLinkedList<int> **dungeonsRoomsIndexes = new QueueLinkedList<int> *(NULL);

  for (int i = 0; i < dungeons::nLevels; i++)
  {
    nRooms = this->numberRooms[i];

    // Initialize the Required Data Structures
    levelRooms = new int[nRooms];

    // Initialize Dungeon Rooms IDs Queue
    dungeonsRoomsIndexes[i] = new QueueLinkedList<int>(dungeons::unasigned);

    // Fill Level Rooms
    for (int j = 0; j < nRooms; j++)
      levelRooms[j] = j;

    // Get Dungeon Room in Random Order
    for (int j = 0; j < nRooms; j++)
    {
      // Create Random Distribution
      n = nRooms - j - 1;
      uniform_int_distribution<int> distLevel(0, n);

      // Get Random Index
      index = distLevel(rd);

      // Store Random Index
      dungeonsRoomsIndexes[i]->enqueue(levelRooms[index]);

      // Remove the Possibility to Get the Given Index Again
      this->swapIntArray(levelRooms, n, index);
    }

    // Deallocate Memory
    delete[] levelRooms;
  }

  return dungeonsRoomsIndexes;
}

// Method to Get the Dungeon Rooms for a Given Level
QueueLinkedList<DungeonRoomPtr> **Dungeons::getDungeonRooms()
{
  int dungeonRoomIndex;
  DungeonRoomPtr dungeonRoom;
  bool hasKey, isEntrance, isExit;

  // Initialize Dungeons Rooms Queue Dynamic Array
  QueueLinkedList<DungeonRoomPtr> **dungeonsRooms = new QueueLinkedList<DungeonRoomPtr> *[dungeons::nLevels];

  // Get Dungeons Rooms Indexes
  QueueLinkedList<int> **dungeonsRoomsIndexes = this->getDungeonRoomsIndexes();

  // Initialize the Required Data Structures
  for (int i = 0; i < dungeons::nLevels; i++)
    dungeonsRooms[i] = new QueueLinkedList<DungeonRoomPtr>(NULL);

  for (int i = 0; i < dungeons::nLevels; i++)
  {
    for (int roomsIdsLength = dungeonsRoomsIndexes[i]->getLength(); roomsIdsLength > 0; roomsIdsLength--)
    {
      hasKey = isEntrance = isExit = false;

      // Get Dungeon Room Index
      dungeonRoomIndex = dungeonsRoomsIndexes[i]->dequeue();

      // Check if the Given Dungeon Room is Special
      for (int j = 0; j < dungeons::nSpecialRooms; j++)
        if (this->specialRooms[i][j] == dungeonRoomIndex)
        {
          // Check which Type of Special Room is
          switch (j)
          {
          case dungeons::keyIndex:
            hasKey = true;
            break;

          case dungeons::entranceIndex:
            isEntrance = true;
            break;

          case dungeons::exitIndex:
            isExit = true;
            break;
          }

          break;
        }

      // Create Dungeon Room
      dungeonRoom = new DungeonRoom(hasKey, isEntrance, isExit);

      // Add Dungeon Room
      dungeonsRooms[i]->enqueue(dungeonRoom);
    }

    // Deallocate Memory
    delete dungeonsRoomsIndexes[i];
  }

  // Deallocate Memory
  delete[] dungeonsRoomsIndexes;

  return dungeonsRooms;
}

// Method to Get Random Dungeon Rooms Connections for Each Level
void Dungeons::getDungeonRoomsConns()
{
  SingleLinkedList<Edge> **nodesEdges;
  SingleLinkedList<int> *srcNodeIds;
  Edges dungeonEdges;
  Edge nodeEdge;
  bool isSpecial;
  int nRooms, nonSpecialRooms, maxEdges, nodeEdgesLength, specialCounter, nonSpecialCounter, **edges, **edgesIndexes, *nEdges, *edgesCounter, srcNodeId, dstNodeId, srcNodeIdIndex, dstNodeIdIndex, possibleEdgeIndex, entranceId, keyId, exitId, entranceIdIndex, keyIdIndex, exitIdIndex, n;

  for (int i = 0; i < dungeons::nLevels; i++)
  {
    nRooms = this->numberRooms[i];
    maxEdges = nRooms - 1;

    // Initialize Nodes Edges Single Linked List
    nodesEdges = new SingleLinkedList<Edge> *[nRooms];

    // Initialize the Required Data Structures
    edges = new int *[nRooms];
    edgesIndexes = new int *[nRooms];
    nEdges = new int[nRooms];
    edgesCounter = new int[nRooms];

    // Get Entrance, Key and Exit Node ID
    entranceId = this->specialRooms[i][dungeons::entranceIndex];
    entranceIdIndex = getNodeIndex(entranceId);

    keyId = this->specialRooms[i][dungeons::keyIndex];
    keyIdIndex = getNodeIndex(keyId);

    exitId = this->specialRooms[i][dungeons::exitIndex];
    exitIdIndex = getNodeIndex(exitId);

    for (int j = 0; j < nRooms; j++)
    {
      isSpecial = j == entranceIdIndex || j == keyIdIndex || j == exitIdIndex;
      edgesCounter[j] = 0;

      // Initialize Node Edges Single Linked List
      nodesEdges[j] = new SingleLinkedList<Edge>(NULL);

      // Initialize the Given Dynamic Array
      edges[j] = new int[maxEdges];
      edgesIndexes[j] = new int[nRooms];

      // Fill Possible Edges and Possible Edges Indexes with 'dungeons::unasigned'
      fill(edges[j], edges[j] + maxEdges, dungeons::unasigned);
      fill(edgesIndexes[j], edgesIndexes[j] + nRooms, dungeons::unasigned);

      // Get the Possible Edges per Node
      for (int k = 0; k < nRooms; k++)
      {
        // Node can not be Connected with Itself
        if (j == k)
          continue;

        // Entrance Node, Exit Node and Key Room can not be Directly Connected
        else if (isSpecial)
          if (k == entranceIdIndex || k == exitIdIndex || k == keyIdIndex)
            continue;

        // Set Possible Node Connection ID
        edges[j][edgesCounter[j]] = getNodeId(k);
        edgesCounter[j]++;
      }
    }

    // Shuffle Rooms Possible Connections
    for (int j = 0; j < nRooms; j++)
      for (int k = 0; k < maxEdges && k < edgesCounter[j]; k++)
      {
        if (k != maxEdges)
        {
          // Distribution of Nodes IDs Indexes
          n = edgesCounter[j] - 1;
          uniform_int_distribution<int> distNodesIdIndexes(k, n);

          // Get Random Node ID Index
          dstNodeIdIndex = distNodesIdIndexes(rd);
        }
        else
          dstNodeIdIndex = k;

        // Store Node ID Index
        edgesIndexes[edges[j][dstNodeIdIndex]][j] = k;

        // Shuffle Rooms
        this->swapIntArray(edges[j], dstNodeIdIndex, k, edges[j][k]);
      }

    // Add at Least One Pseudo-Random Connection, to Prevent Isolated Nodes
    srcNodeIds = new SingleLinkedList<int>(dungeons::unasigned);

    nonSpecialCounter = 0;
    nonSpecialRooms = nRooms - dungeons::nSpecialRooms;

    for (int j = 0; j < nRooms - 1; j++)
    {
      specialCounter = 0;

      // Get Dungeon Node ID and Push it Back
      while (j + specialCounter < nRooms)
      {
        srcNodeId = j != 0 ? dstNodeId : this->nodesIds[i]->removeBack();

        if (srcNodeId == entranceId || srcNodeId == keyId || srcNodeId == exitId)
          specialCounter++;

        else
        {
          srcNodeIds->pushBack(srcNodeId);
          break;
        }
      }

      while (true)
      {
        dstNodeId = this->nodesIds[i]->removeBack();

        if (dstNodeId == entranceId || dstNodeId == keyId || dstNodeId == exitId)
          specialCounter++;

        else
        {
          dstNodeIdIndex = getNodeIndex(dstNodeId);
          break;
        }
      }
      j += specialCounter;

      // Check if there's a Special Room that should be Connected with the Destination Node
      if (nonSpecialCounter == 0)
        // Add Entrance Room
        srcNodeIds->pushBack(entranceId);

      if (nonSpecialCounter == (nonSpecialRooms - 1) / 2)
        // Add Key Room
        srcNodeIds->pushBack(keyId);

      if (nRooms <= 5 && nonSpecialCounter == nonSpecialRooms - 1 || nRooms > 6 && nonSpecialCounter == nonSpecialRooms - 2)
        // Add Exit Room
        srcNodeIds->pushBack(exitId);

      // Insert Node Edge to its Corresponding Single Linked Lists
      for (int srcNodeIdsLength = srcNodeIds->getLength(); srcNodeIdsLength > 0; srcNodeIdsLength--)
      {
        // Get Source Node ID and ID Index
        srcNodeId = srcNodeIds->remove();
        srcNodeIdIndex = this->getNodeIndex(srcNodeId);

        // Check if the Node has Reached the Maximum Number of Paths
        if (nodesEdges[srcNodeIdIndex]->getLength() < dungeons::maxRoomEdge)
          // Add Node Edge
          this->pushEdge(nodesEdges, srcNodeIdIndex, dstNodeIdIndex, srcNodeId, dstNodeId);

        this->removePossibleEdge(edges, edgesCounter, edgesIndexes, srcNodeIdIndex, edgesIndexes[dstNodeIdIndex][srcNodeIdIndex]);
        this->removePossibleEdge(edges, edgesCounter, edgesIndexes, dstNodeIdIndex, edgesIndexes[srcNodeIdIndex][dstNodeIdIndex]);
      }
      nonSpecialCounter++;
    }

    // Distribution of the Number of Edges per Node for Non-Special Rooms
    uniform_int_distribution<int> distNumberEdges(dungeons::minRoomEdge, dungeons::maxRoomEdge);

    for (int j = 0, suggested; j < nRooms; j++)
    {
      // Get First Node ID and Push it Back
      nodeEdgesLength = nodesEdges[j]->getLength();
      srcNodeId = this->nodesIds[i]->removeBack();

      // Check if the Given Room is Special
      isSpecial = srcNodeId == entranceId || srcNodeId == keyId || srcNodeId == exitId;

      // Get the Suggested Number of Nodes Edges to Set
      suggested = isSpecial ? dungeons::nSpecialRoomEdge : distNumberEdges(rd);
      nEdges[j] = (!isSpecial && nodeEdgesLength > suggested) ? nodeEdgesLength : suggested;
    }

    // Get 1-3 Connections for Each Dungeon Room
    for (int nodesIdsLength = this->nodesIds[i]->getLength(); nodesIdsLength > 0; nodesIdsLength--)
    {
      // Get Dungeon Node ID and Push it Back
      srcNodeId = this->nodesIds[i]->removeBack();
      srcNodeIdIndex = getNodeIndex(srcNodeId);

      // Check if the Node Already have Enough Edges
      while (nodesEdges[srcNodeIdIndex]->getLength() < nEdges[srcNodeIdIndex])
      {
        // Check Possible Edges Counter
        if (edgesCounter[srcNodeIdIndex] == 0)
          break;

        // Get First Random Node ID
        dstNodeId = edges[srcNodeIdIndex][0];
        dstNodeIdIndex = getNodeIndex(dstNodeId);

        // Remove the Possibility to Get the Same Edge Index
        this->removePossibleEdge(edges, edgesCounter, edgesIndexes, srcNodeIdIndex);
        this->removePossibleEdge(edges, edgesCounter, edgesIndexes, dstNodeIdIndex, edgesIndexes[srcNodeIdIndex][dstNodeIdIndex]);

        // Check if the Destination Node ID Already Reached the Maximum Number of Nodes Connections
        if (nodesEdges[dstNodeIdIndex]->getLength() >= nEdges[dstNodeIdIndex])
          continue;

        // Insert Node Edge to its Corresponding Queues
        this->pushEdge(nodesEdges, srcNodeIdIndex, dstNodeIdIndex, srcNodeId, dstNodeId);
      }
    }

    for (int j = 0; j < nRooms; j++)
    {
      // Create Dungeon Edges
      dungeonEdges = new WeightedNodeEdges(getNodeId(j), nodesEdges[j]);

      // Add Dungeon Room Connections
      this->roomsConns[i]->pushBack(dungeonEdges);
    }

    // Deallocate Memory
    for (int j = 0; j < nRooms; j++)
      delete[] edges[j], edgesIndexes[j];

    delete[] edges, edgesIndexes, edgesCounter, nEdges, nodesEdges;
  }
}

// Method to Get the Shortest Path between Two Nodes
SingleLinkedList<int> *Dungeons::getShortestPath(int levelIndex, int startNodeId, int endNodeId)
{
  bool *currVisitedNodes, found = false;
  int *currUnvisitedNodesId, currIndex, nodeId, prevNodeId, unvisitedNodeId, nRooms, currNodeId, currDstId, currWeight, visitedNode, currEdgesLength, visitedCounter, unvisitedCounter;
  Edge currEdge;
  Edges currNodeEdges;
  SingleLinkedList<Edges> *nodeEdges;
  QueueLinkedList<Edge> *currEdges;
  SingleLinkedList<int> *path;
  SingleLinkedList<int> *unvisitedNodes, *visitedNodes, *prevNodeIds;
  SingleLinkedList<Edge> *shortestDistances;

  nRooms = this->numberRooms[levelIndex];
  nodeEdges = this->roomsConns[levelIndex];

  // Initialize Required Queues
  unvisitedNodes = new SingleLinkedList<int>(dungeons::unasigned);
  visitedNodes = new SingleLinkedList<int>(dungeons::unasigned);
  prevNodeIds = new SingleLinkedList<int>(dungeons::unasigned);
  shortestDistances = new SingleLinkedList<Edge>(NULL);
  path = new SingleLinkedList<int>(dungeons::unasigned);

  // Fill Shortest Distances, Visited, Unvisited Nodes
  visitedNodes->pushBack(startNodeId);
  prevNodeIds->pushBack(dungeons::unasigned);
  shortestDistances->pushBack(new WeightedNodeEdge(startNodeId, 0));

  for (int i = 0; i < nRooms; i++)
  {
    nodeId = this->nodesIds[levelIndex]->removeBack();

    if (nodeId == startNodeId)
      continue;

    unvisitedNodes->push(nodeId);
  }

  currNodeId = startNodeId;
  currWeight = 0;
  currIndex = 0;

  // Apply Dijkstra's Algoritm
  while (!found)
  {
    // Get Current Node Edges
    for (int nodeEdgesLength = nodeEdges->getLength(); nodeEdgesLength > 0; nodeEdgesLength--)
    {
      currNodeEdges = nodeEdges->removeBack();

      if (currNodeEdges->getSrcId() == currNodeId)
        break;
    }

    // Get Edges
    currEdges = currNodeEdges->getEdges();
    currEdgesLength = currEdges->getLength();

    // Check if the Nodes are Unvisited
    currVisitedNodes = new bool[currEdgesLength];
    fill(currVisitedNodes, currVisitedNodes + currEdgesLength, false);
    visitedCounter = 0;

    for (int visitedNodesLength = visitedNodes->getLength(); visitedNodesLength > 0; visitedNodesLength--)
    {
      visitedNode = visitedNodes->removeBack();

      // Check if there's a Visited Node
      for (int i = 0; i < currEdgesLength; i++)
      {
        currEdge = currEdges->removeBack();

        if (currVisitedNodes[i])
          continue;

        else if (visitedNode == currEdge->getDstId())
        {
          currVisitedNodes[i] = true;
          visitedCounter++;
        }
      }
    }

    currUnvisitedNodesId = new int[currEdgesLength - visitedCounter];
    unvisitedCounter = 0;

    for (int i = 0; i < currEdgesLength; i++)
    {
      currEdge = currEdges->removeBack();

      if (currVisitedNodes[i])
        continue;

      // Add Unvisited Nodes
      currDstId = currEdge->getDstId();
      currUnvisitedNodesId[unvisitedCounter++] = currDstId;

      // Add as Visited Nodes
      visitedNodes->pushBack(currDstId);
      shortestDistances->pushBack(new WeightedNodeEdge(currDstId, currEdge->getWeight() + currWeight));
      prevNodeIds->pushBack(currNodeId);

      // Check if the Path has been Completed
      if (currDstId == endNodeId)
      {
        prevNodeId = currNodeId;
        currNodeId = endNodeId;
        found = true;
        break;
      }
    }

    // Shortcut
    if (found)
      break;

    // Removed Unvisited Nodes
    for (int unvisitedNodesLength = unvisitedNodes->getLength(); unvisitedNodesLength > 0; unvisitedNodesLength--)
    {
      unvisitedNodeId = unvisitedNodes->removeBack();

      for (int i = 0; i < unvisitedCounter; i++)
        if (unvisitedNodeId == currUnvisitedNodesId[i])
        {
          unvisitedNodes->removeAt(-1);
          break;
        }
    }

    // Get Current and Previous Node ID
    currNodeId = visitedNodes->get(++currIndex);
    prevNodeId = prevNodeIds->get(currIndex);

    // Get Current Weight
    currWeight = shortestDistances->get(currIndex)->getWeight();

    // Deallocate Memory
    delete[] currUnvisitedNodesId, currVisitedNodes;
  }

  // Get Path
  path->push(currNodeId);

  for (int visitedNodesLength = visitedNodes->getLength(); visitedNodesLength > 0; visitedNodesLength--)
  {
    // Add Nodes that are Part of the Shortest Path
    nodeId = visitedNodes->pop();

    if (nodeId != prevNodeId)
      prevNodeIds->pop();

    else
    {
      // Add Node
      path->push(nodeId);
      currNodeId = nodeId;
      prevNodeId = prevNodeIds->pop();
    }
  }

  // Deallocate Memory
  delete unvisitedNodes, visitedNodes, shortestDistances, prevNodeIds;

  return path;
}

// Method to Swap the Values of Two Array Cells and Assign 'dungeons::unasigned' at the 'swapFromIndex' Index
void Dungeons::swapIntArray(int *array, int swapFromIndex, int swapToIndex, int valueFromIndex)
{
  int toSwap;

  // Remove the Possibility to Get the Same Edge Index
  toSwap = array[swapFromIndex];
  array[swapToIndex] = toSwap;
  array[swapFromIndex] = valueFromIndex;
}

// Method to Push a Given Edge between Two Nodes
void Dungeons::pushEdge(SingleLinkedList<Edge> **nodesEdges, int srcNodeIdIndex, int dstNodeIdIndex, int srcNodeId, int dstNodeId)
{
  // Add Edge between the Given Two nodes
  nodesEdges[srcNodeIdIndex]->pushBack(new WeightedNodeEdge(dstNodeId, dungeons::edgeWeight));
  nodesEdges[dstNodeIdIndex]->pushBack(new WeightedNodeEdge(srcNodeId, dungeons::edgeWeight));
}

// Method to Remove a Possible Edge from its Given Arrays
void Dungeons::removePossibleEdge(int **edges, int *edgesCounter, int **edgesIndexes, int srcNodeIdIndex, int toNodeIdIndex)
{
  int fromIdIndex, toIdIndex, fromValue, toValue;

  // Edge doesn't Exist
  if (toNodeIdIndex <= dungeons::unasigned || edgesCounter[srcNodeIdIndex] == 0)
    return;

  // Get the Required Data
  fromIdIndex = edgesCounter[srcNodeIdIndex] - 1;
  fromValue = edges[srcNodeIdIndex][fromIdIndex];
  toIdIndex = toNodeIdIndex;
  toValue = edges[srcNodeIdIndex][toIdIndex];

  // Update Edge Indexes
  edgesIndexes[fromValue][srcNodeIdIndex] = toIdIndex;
  edgesIndexes[toValue][srcNodeIdIndex] = dungeons::unasigned;

  // Swap Values
  this->swapIntArray(edges[srcNodeIdIndex], fromIdIndex, toIdIndex);
  edgesCounter[srcNodeIdIndex]--;
}

/*
// Method to Play the Dungeons Without Dragons Game
void Dungeons::playGame()
{
  SingleLinkedList<int> *conns;
  int currLevel = 0, currRoom = this->specialRooms[currLevel][dungeons::entranceIndex];
  bool hasKey = false;

  while (currLevel < 4)
  {
    ostringstream title, msg;

    // Get Dungeon Title
    title << "Dungeon " << currLevel + 1 << ". Room " << currRoom;

    // Get Possible Connections
    printTitle(title.str());

    msg << "\nPossible Connections: ";
  }
}
*/

#endif