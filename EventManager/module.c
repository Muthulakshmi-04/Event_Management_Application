#include "event_manager.h"

// Create a new module
Module* create_module(int id, const char *name) {
    Module *new_module = (Module *)malloc(sizeof(Module));
    if (!new_module) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    new_module->module_id = id;
    strcpy(new_module->module_name, name);
    new_module->prev = NULL;
    new_module->next = NULL;
    return new_module;
}

// Add module to the list
void add_module(Module **head, Module *module) {
    if (!module) return;
    module->next = *head;
    if (*head) (*head)->prev = module;
    *head = module;
}


void delete_module(Module **head, Event *event_head, int id) {
    Module *temp = *head;
    while (temp) {
        if (temp->module_id == id) {
            if (temp->prev) temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            if (temp == *head) *head = temp->next;

            // Remove module reference from all events
            Event *event = event_head;
            while (event) {
                ModuleNode **mod_list = &event->module_list;
                while (*mod_list) {
                    if ((*mod_list)->module->module_id == id) {
                        ModuleNode *to_delete = *mod_list;
                        *mod_list = to_delete->next;
                        free(to_delete);
                        break;
                    }
                    mod_list = &((*mod_list)->next);
                }
                event = event->next;
            }

            free(temp);
            printf("Module %d deleted\n", id);
            return;
        }
        temp = temp->next;
    }
    printf("Module %d not found\n", id);
}

// Print all modules
void print_modules(Module *head) {
    while (head) {
        printf("Module ID: %d, Name: %s\n", head->module_id, head->module_name);
        head = head->next;
    }
}

