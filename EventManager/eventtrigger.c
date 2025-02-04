#include "event_manager.h"

void trigger_event(Event *head, int event_id) {
    while (head) {
        if (head->event_id == event_id) {
            printf("Triggering event: %s\n", head->event_name);
            ModuleNode *mod_list = head->module_list;
            while (mod_list) {
                printf("Executing module: %s\n", mod_list->module->module_name);
                mod_list = mod_list->next;
            }
            return;
        }
        head = head->next;
    }
    printf("Event ID %d not found\n", event_id);
}

