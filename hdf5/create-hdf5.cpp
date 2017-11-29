#ifdef OLD_HEADER_FILENAME
#include <iostream.h>
#else
#include <iostream>
#endif

#include <time.h>
#include <fstream>
#include <string>
#include "H5Cpp.h"
//#include <omp.h>
using namespace H5;
using namespace std;

#define NUM_THREADS 20

const H5std_string  FILE_NAME( "data.h5" );
const H5std_string  DATASET_NAME( "DoubleArray" );
const int   NX = 1000;                    // dataset dimensions
const int   NY = 10000;
const int   RANK = 2;
hsize_t chunk_dims[2] = { 20, 20 }; // chunk dimensions

void record_array( double (*st_array)[NY], const int shape[2], ofstream& dumpObj) {
      
      for(int i = 0; i < shape[0]-1; i++) {
        for(int j=0; j < shape[1]-1; j++) {
         dumpObj << st_array[i][j] << ", ";
         }
        dumpObj << st_array[i][shape[1]-1] << std::endl;
      }
   }

int main ()
{
   /*
    * Data initialization.
    */
   int i, j;
   double (*data)[NY] = new double[NX][NY];          // buffer for data to write
 //   #pragma omp parallel for
   for (j = 0; j < NX; j++)
   {
      for (i = 0; i < NY; i++)
        data[j][i] = i + j;
   }


   /*
    * Grabbed the following hdf5 snippet from hdf5 documentation 
    */
      H5File file( FILE_NAME, H5F_ACC_TRUNC );

      hsize_t dimsf[2];              // dataset dimensions
      dimsf[0] = NX;
      dimsf[1] = NY;
      DataSpace dataspace( RANK, dimsf );

      DataType  datatype( H5::PredType::NATIVE_FLOAT );

    // Modify dataset creation property to enable chunking
    //DSetCreatPropList  *plist = new  DSetCreatPropList;
    //plist->setChunk(2, chunk_dims);

    // Set ZLIB (DEFLATE) Compression using level 6.
    // To use SZIP compression comment out this line.
    // plist->setDeflate(6);

      double h5time0 = clock();
      DataSet dataset = file.createDataSet( DATASET_NAME, datatype, dataspace );
      dataset.write( data, PredType::NATIVE_FLOAT );
      double h5time1 = clock();


      // delete plist;
      // cout the time required to write to file
    cout << "HDF5 time: " << (h5time1 - h5time0)/CLOCKS_PER_SEC << " seconds" << std::endl;

    // initialize the file stream and prepare for csv writer
    ofstream datafile("data.csv" ); 

    int array_shape[2];
    array_shape[0]=NX;
    array_shape[1]=NY;

    double csvtime0 = clock();
    // export data in csv data format
    record_array(data, array_shape, datafile );
    double csvtime1 = clock();
    cout << "CSV time: " << (csvtime1 - csvtime0)/CLOCKS_PER_SEC<< " seconds" << std::endl;


   return 0;
}


   
