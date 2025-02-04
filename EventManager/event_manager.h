#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for Module (Doubly Linked List)
typedef struct Module {
    int module_id;               // Unique Module ID
    char module_name[50];        // Module name
    struct Module *prev, *next;  // Doubly linked list pointers
} Module;

// Struct for Module Node (Used Inside Events)
typedef struct ModuleNode {
    Module *module;             // Pointer to a registered module
    struct ModuleNode *next;    // Next module in the event's module list
} ModuleNode;

// Struct for Event (Doubly Linked List)
typedef struct Event {
    int event_id;               // Unique Event ID
    char event_name[50];        // Event name
    ModuleNode *module_list;    // Pointer to linked list of registered modules
    struct Event *prev, *next;  // Doubly linked list pointers
} Event;

// Event Management Functions
Event* add_event(Event **head, int id, const char *name);
void delete_event(Event **head, int id);
void print_events(Event *head);

// Module Management Functions
Module* create_module(int id, const char *name);
void add_module(Module **head, Module *module);
void delete_module(Module **head, Event *event_head, int id);
void print_modules(Module *head);
void register_module(Event *event, Module *module);

// Event Trigger Function
void trigger_event(Event *head, int event_id);

#endif // EVENT_MANAGER_H

