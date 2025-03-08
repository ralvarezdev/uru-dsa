#include <string>

using std::string;

#ifndef NAMESPACES_H
#define NAMESPACES_H

namespace setup
{
  // Debug Mode
  const bool debugMode = true;
}

namespace terminal
{
  // - ANSI Escape Code
  const string reset = "\x1b[0m"; // Reset Terminal Text Format to Default
  const string clear = "\033c";   // Clear Terminal

  // - Format Constants
  const string tab1 = string(3, ' '); // String with 3 whitespaces
  const string tab2 = string(8, ' '); // String with 8 whitespaces
  const bool applyBg = true;          // Add Customed Background Color
  const bool applyFg = true;          // Add Customed Foreground Color

  // --- Color Command Created Using ralvarezdev's Minigrep. URL: https://github.com/ralvarezdev/minigrep

  // - Normal State
  const string sgrBg = "\x1b[48;2;153;204;255m"; // Command to Change Text Background Color
  const string sgrFg = "\x1b[38;2;32;32;32m";    // Command to Change Text Foreground Color

  // - Warning (On Error)
  const string sgrBgError = "\x1b[48;2;255;153;153m";
  const string sgrFgError = "\x1b[38;2;32;32;32m";

  // - Number of Characters
  const int nChar = 100; // Max Number of Characters being Printed on Each Line
}

namespace dungeons
{
  // Enums Should be at the Beginning
  // - Dungeons Commands
  namespace cmds
  {
    const int startGame = 's';
    const int debugMode = 'd';
    const int help = 'h';
    const int exit = 'e';
  };

  // Dungeon Rooms per Level
  const int level1Rooms = 5;
  const int level2Rooms = 8;
  const int level3Rooms = 15;
  const int nLevels = 3;
  const int nSpecialRooms = 3;

  // Dungeon First Node ID
  const int firstNodeId = 0;

  // Dungeon Room Edges (for Non-Special Rooms)
  const int minRoomEdge = 2;
  const int maxRoomEdge = 3;

  // ... (for Special Rooms)
  const int nSpecialRoomEdge = 1;

  // Dungeon Level Special Rooms Indexes
  const int entranceIndex = 0;
  const int keyIndex = 1;
  const int exitIndex = 2;

  // Undirected Graph Edge Weight
  const int edgeWeight = 1;

  // Unasigned Flag
  const int unasigned = -1;
}

#endif