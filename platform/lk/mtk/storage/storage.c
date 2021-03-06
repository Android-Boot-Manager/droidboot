#include "lvgl/lvgl.h"
#include <kernel/thread.h>
#include <platform/mtk_key.h>
#include <target/cust_key.h>
#include <sys/types.h>
#include <reg.h>
#include <debug.h>
#include <err.h>
#include <reg.h>
#include <lib/fs.h>
#include <video.h>
#include <platform/mt_typedefs.h>
#include <platform/boot_mode.h>
#include <platform/mt_reg_base.h>
#include <platform/mt_gpt.h>
#include <platform/mtk_wdt.h>
#include <lib/bio.h>
#include <part_interface.h>
#include <block_generic_interface.h>
#include <lib/partition.h>
#include "config.h"
#include <platform/mt_leds.h>

#define MMC_HOST_ID                 0

typedef struct mmc_sdhci_bdev {
  	bdev_t dev; // base device
  
  	struct mmc_device *mmcdev;
  } mmc_sdhci_bdev_t;


static ssize_t bdev_read_block_data(struct bdev *_bdev, void *buf, bnum_t block, size_t len, size_t len1)
{
        unsigned long long ptn = 0;
	unsigned long long size = 0;
	int index = 0; 
    unsigned int part_id;
   index = partition_get_index("cache");
    ptn = partition_get_offset(index);
    part_id = partition_get_region(index);
    emmc_read(8, ptn+block , (void *)buf, len1);
}


void platform_storage_init(){
    bio_init();
    struct mmc_card *card;
    card = mmc_get_card(MMC_HOST_ID);
    part_dev_t *dev;
    dev = mt_part_get_device();
	char name[20]= "cache";
	mmc_sdhci_bdev_t *bdev = malloc(sizeof(mmc_sdhci_bdev_t));
	/* set up the base device */
    bio_initialize_bdev(&bdev->dev, name, card->blklen,partition_get_size(33)/card->blklen);
	/* our bits */
	bdev->mmcdev = dev;
	bdev->dev.read_block = bdev_read_block_data;
	/* register it */
	bio_register_device(&bdev->dev);
}
