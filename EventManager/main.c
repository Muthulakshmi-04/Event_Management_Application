#include "event_manager.h"

int main() {
    Event *event_head = NULL;
    Module *module_head = NULL;
    int choice;

    while (1) {
        printf("\n===== Event Manager =====\n");
        printf("1. Add Event\n");
        printf("2. Delete Event\n");
        printf("3. Add Module\n");
        printf("4. Delete Module\n");
        printf("5. Register Module to Event\n");
        printf("6. Trigger Event\n");
        printf("7. Print Events\n");
        printf("8. Print Modules\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 9) break;

        int id;
        char name[50];

        switch (choice) {
            case 1:
                printf("Enter event ID: ");
                scanf("%d", &id);
                printf("Enter event name: ");
                scanf("%s", name);
                add_event(&event_head, id, name);
                break;

            case 2:
                printf("Enter event ID to delete: ");
                scanf("%d", &id);
                delete_event(&event_head, id);
                break;

            case 3:
                printf("Enter module ID: ");
                scanf("%d", &id);
                printf("Enter module name: ");
                scanf("%s", name);
                add_module(&module_head, create_module(id, name));
                break;

            case 4:
                printf("Enter module ID to delete: ");
                scanf("%d", &id);
                delete_module(&module_head, event_head, id);
                break;

            case 5:
                printf("Enter event ID: ");
                scanf("%d", &id);
                Event *event = event_head;
                while (event && event->event_id != id) event = event->next;

                if (!event) {
                    printf("Event not found!\n");
                    break;
                }

                printf("Enter module ID: ");
                scanf("%d", &id);
                Module *module = module_head;
                while (module && module->module_id != id) module = module->next;

                if (!module) {
                    printf("Module not found!\n");
                    break;
                }

                register_module(event, module);
                printf("Module %d registered to event %d.\n", module->module_id, event->event_id);
                break;

            case 6:
                printf("Enter event ID to trigger: ");
                scanf("%d", &id);
                trigger_event(event_head, id);
                break;

            case 7:
                print_events(event_head);
                break;

            case 8:
                print_modules(module_head);
                break;

            default:
                printf("Invalid choice!\n");
        }
    }

    printf("Exiting...\n");
    return 0;
}

