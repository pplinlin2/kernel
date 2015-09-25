#include <linux/module.h>
#include <linux/fs.h>
/*
register_filesystem, unregister_filesystem,  
simple_release_fs, 
*/
#include <linux/pagemap.h>
#include <linux/mount.h>
#include <linux/init.h>
#include <linux/namei.h>

#define FS_MAGIC 0x64668735
struct vfsmount *fs_mount;
int fs_mount_count;

static int fs_fill_super(struct super_block *sb, void *data, int silent)
{
	static struct tree_descr debug_files[] = {{""}};

	return simple_fill_super(sb, FS_MAGIC, debug_files);
}

static int fs_get_sb(struct file_system_type *fs_type, int flags, const char *dev_name, void *data, struct vfsmount *mnt)
{
	return get_sb_single(fs_type, flags, data, fs_fill_super, mnt);
}

struct file_system_type fs_type = {
	.owner   = THIS_MODULE, 
	.name    = "myfs", 
	.get_sb  = fs_get_sb, 
	.kill_sb = kill_litter_super, 
};

struct dentry *fs_create_dir(const char *name, struct dentry *parent)
{
	if(!parent){
		if(fs_mount && fs_mount->mnt_sb){
			parent = fs_mount->mnt_sb->s_root;
		}
	}

	mutex_lock(&parent->d_inode->i_mutex);
	struct dentry *dentry  = lookup_one_len(name, parent, strlen(name));
	struct inode *dir      = parent->d_inode;
	struct super_block *sb = dir->i_sb;
	struct inode *inode    = new_inode(sb);

	inode->i_mode    = S_IFDIR;
	inode->i_uid     = 1000;
	inode->i_gid     = 1000;
	inode->i_blocks  = 0;
	inode->i_atime   = inode->i_mtime = inode->i_ctime = CURRENT_TIME;
	inode->i_op      = &simple_dir_inode_operations;
	inode->i_fop     = &simple_dir_operations;

	d_instantiate(dentry, inode);
	dget(dentry);
	printk("create a dir\n");
	mutex_unlock(&parent->d_inode->i_mutex);

	return dentry;
}

int __init fs_init()
{
	register_filesystem(&fs_type);
	fs_mount = kern_mount(&fs_type);

	struct dentry *dir;
	dir = fs_create_dir("The Shawshank Redemption", NULL);
	dir = fs_create_dir("The Godfather", NULL);

	return 0;
}

void __exit fs_exit()
{
	simple_release_fs(&fs_mount, &fs_mount_count);
	unregister_filesystem(&fs_type);
}

MODULE_LICENSE("GPL");
module_init(fs_init);
module_exit(fs_exit);
