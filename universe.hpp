#pragma once

#include <vector>
#include <memory>

// THE ENTIRE UNIVERSE!!!!!!!!

struct Door;
struct Room;
typedef std::unique_ptr<Door> DoorPtr;
typedef std::unique_ptr<Room> RoomPtr;

struct Room {
    std::array<DoorPtr, 4> doors;
    // Additional info for things and stuff.
    enum Corner {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };
};

struct Door {
    Room* target;
    Room::Corner dest;
    Room::Corner source;
};


std::vector<RoomPtr> generateWorld(size_t size);
