import os
import random
import shutil


path = os.getcwd() # get current path
category = []


def mkdir():
    global category
    
    if not os.path.exists(path + '/Training Data') and not os.path.exists(path + '/Testing Data'):
        items = os.listdir(path) # get all files(hidden, folder, file)
        for item in items:
            if os.path.isdir(item): # judge is directory
                category.append(item)
        for t in category:
            os.makedirs(path + '/Training Data/' + t)
            os.makedirs(path + '/Testing Data/' + t)

    else:
        items = os.listdir(path)
        for item in items:
            if not item == 'Training Data' and not item == 'Testing Data' and not item.startswith('.') and os.path.isdir(item): # filter hidden files
                category.append(item)


# filter non images
def get_images_num(path):
    c = 0
    imgs = []
    for i in os.listdir(path):
        name, suf = os.path.splitext(i) # get image suffix
        if suf == '.jpg':
            c+=1
            imgs.append(i)
    return imgs, c


def seperate():
    print('%d categories' % len(category), category)
    
    for i in category:
        images, num = get_images_num(path + '/' + i)
        train_num = int(num * 0.8)
        test_num = num - train_num
        print('Total %d images of category %s' % (num, i))
        print('--Training num is %d' % train_num)
        print('--Testing num is %d' % test_num)
        
        # get train images by random
        train_set = random.sample(images, train_num)
        
        # move train images
        for image in train_set:
            old_path = path + '/' + i + '/' + image
            new_path = path + '/Training Data/' + i + '/' + image
            shutil.move(old_path, new_path)

        # move test images
        test_set, _ = get_images_num(path + '/' + i)
        for image in test_set:
            old_path = path + '/' + i + '/' + image
            new_path = path + '/Testing Data/' + i + '/' + image
            shutil.move(old_path, new_path)

        # evaluate wheter sperate is successful
        _, r_train = get_images_num(path + '/Training Data/' + i)
        _, r_test = get_images_num(path + '/Testing Data/' + i)
        
        print('result of train %d' % r_train)
        print('result of test %d' % r_test)
        if r_train == train_num and r_test == test_num:
            print('Sepreate is done!')







    

mkdir()
seperate()




