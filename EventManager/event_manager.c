#include "event_manager.h"

// Add an event
Event* add_event(Event **head, int id, const char *name) {
    Event *new_event = (Event *)malloc(sizeof(Event));
    if (!new_event) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    new_event->event_id = id;
    strcpy(new_event->event_name, name);
    new_event->module_list = NULL;
    new_event->prev = NULL;
    new_event->next = *head;

    if (*head) (*head)->prev = new_event;
    *head = new_event;
    
    return new_event;
}

// Delete an event
void delete_event(Event **head, int id) {
    Event *temp = *head;
    while (temp) {
        if (temp->event_id == id) {
            while (temp->module_list) {
                ModuleNode *to_delete = temp->module_list;
                temp->module_list = to_delete->next;
                free(to_delete);
            }
            if (temp->prev) temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            if (temp == *head) *head = temp->next;

            free(temp);
            printf("Event %d deleted\n", id);
            return;
        }
        temp = temp->next;
    }
    printf("Event %d not found\n", id);
}
void register_module(Event *event, Module *module) {
    if (!event || !module) return;
    
    ModuleNode *new_entry = (ModuleNode *)malloc(sizeof(ModuleNode));
    if (!new_entry) {
        printf("Memory allocation failed\n");
        return;
    }
    new_entry->module = module;
    new_entry->next = event->module_list;
    event->module_list = new_entry;
}
void print_events(Event *head) {
    while (head) {
        printf("Event ID: %d, Name: %s\n", head->event_id, head->event_name);
        ModuleNode *mod = head->module_list;
        while (mod) {
            printf("  - Module: %s\n", mod->module->module_name);
            mod = mod->next;
        }
        head = head->next;
    }
}

