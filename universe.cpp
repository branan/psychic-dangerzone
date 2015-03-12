#include "universe.hpp"
#include <random>
#include <set>
#include <iostream>

static bool rooms_connected(Room* r1, Room* r2, std::set<Room*> checked = std::set<Room*>()) {
    if(r1 == r2)
        return true;

    checked.insert(r1);
    for(const auto& door: r1->doors) {
        if(!door) {
            continue;
        }
        auto target = door->target;
        if(checked.find(target) == checked.end()) {
            auto connected = rooms_connected(target, r2, checked);
            if(connected) {
                return true;
            }
            // If we're not connected, we keep searching. Hoping each
            // time that the next leap wil be the leap home.
        }
    }
    return false;
}

static void generate_edge(const std::vector<RoomPtr>& rooms) {
    std::random_device rd;
    std::default_random_engine e(rd());
    std::uniform_int_distribution<size_t> room_selector(0, rooms.size()-1);
    std::uniform_int_distribution<size_t> door_selector(0, 3);

    while(true) {
        auto source = room_selector(e);
        auto dest = room_selector(e);
        auto door = door_selector(e);
        auto exit = door_selector(e);
        if (rooms[source]->doors[door]) continue;

        auto the_door = DoorPtr(new Door);
        the_door->source = Room::Corner(door);
        the_door->dest = Room::Corner(exit);
        the_door->target = rooms[dest].get();
        rooms[source]->doors[door] = std::move(the_door);
        return;
    }
}

std::vector<RoomPtr> generateWorld(size_t size) {
    std::vector<RoomPtr> rooms;
    rooms.resize(size);
    for(auto& ptr: rooms) {
        ptr.reset(new Room);
    }

    // For each pair of rooms:
    // Check if they're connected. If so, do nothing
    // If not, generate random edges until they're connected.
    // If no edges can be generated, remove one that creates a redundant link.
    for(const auto& r1: rooms) {
        for(const auto& r2: rooms) {
            while(!rooms_connected(r1.get(), r2.get())) {
                generate_edge(rooms);
            }
        }
    }

    return rooms;
}
