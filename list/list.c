#include <linux/module.h>

char *dog_name[] = {"Lucky", "Max", "Rocky"};

struct dog{
	char name[80];
	struct list_head dog_entry;
};
struct list_head dog_list;

int __init my_init()
{
	INIT_LIST_HEAD(&dog_list);

	int i;
	int n = sizeof(dog_name)/sizeof(dog_name[0]);
	struct dog *curr;
	for(i = 0; i < n; i++){
		curr = kmalloc(sizeof(struct dog), GFP_KERNEL);
		memset(curr, 0, sizeof(struct dog));
		sprintf(curr->name, "%s", dog_name[i]);
		list_add(&curr->dog_entry, &dog_list);
	}

	list_for_each_entry(curr, &dog_list, dog_entry){
		printk("insert %s\n", curr->name);
	}
	
	return 0;
}

void __exit my_exit()
{
	struct dog *curr, *next;
	list_for_each_entry_safe(curr, next, &dog_list, dog_entry){
		list_del(&curr->dog_entry);
		printk("delete %s\n", curr->name);
	}
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
