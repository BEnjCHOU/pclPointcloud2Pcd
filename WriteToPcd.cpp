#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <fstream>
#include <sstream>
#include <string>

// read file function and return pointcloud
pcl::PointCloud<pcl::PointXYZ>::Ptr ReadFilePointCloud(int frame)
{
    std::string source = "/Users/aemass-cheanwu/dev/hk_demo/pclDemo/17_02_2019_16_46_01/M8-192.168.1.9/frame-";
    std::string file_type = ".txt";
    std::string file = source + std::to_string(frame) + file_type;
    std::ifstream infile(file);
    // pcl output
    std::vector<pcl::PointCloud<pcl::PointXYZ>> output;
    // pcl statements
    pcl::PointCloud<pcl::PointXYZ>::Ptr DefaultData (new pcl::PointCloud<pcl::PointXYZ>);
    // read file
    for(std::string line; std::getline(infile, line);)
    {
        // create structure
        pcl::PointXYZ Points;
        std::istringstream in (line);
        in >> Points.x >> Points.y >> Points.z;
        DefaultData->push_back(Points);
    }
    return DefaultData;
}

// pcl save point cloud as pcd file
void saveToPcd( pcl::PointCloud< pcl::PointXYZ >::Ptr cloud, int counting, std::string filename )
{
        cloud->width = cloud->points.size ();
        cloud->height = 1;
        cloud->is_dense = true;
        std::string outputFile;
        outputFile =  filename + "-" + std::to_string(counting) + ".pcd";
        pcl::io::savePCDFileASCII (outputFile, *cloud);
}

int main ()
{
    const int FILE_COUNTER_END = 18815;
    // point cloud to save
    for(int i = 0 ; i < FILE_COUNTER_END ; ++i)
    {
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
        cloud = ReadFilePointCloud(i);
        std::string filename;
        filename = "../raw_cloud_16/raw_cloud";
        saveToPcd(cloud, i, filename);
        std::cout << "save-" << i << std::endl;
    }
    return 0;
}
