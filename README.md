# loader-writer-snippet


## HDF5


HDF5 is much faster than plain text writing.

I tested the speed on a two dimensional array (1000x10000) to h5 and csv and recorded the time.
```
HDF5 time: 0.04 seconds
CSV time: 6.88 seconds
```

The files are

```
59931898 Nov 29 15:24 data.csv
40002144 Nov 29 15:24 data.h5
```
