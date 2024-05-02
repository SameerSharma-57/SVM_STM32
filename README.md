## SVM on Microcontroller

### Code Structure and Running Procedure

- `main.ipynb` Run the ipynb file. 
- All the related header files needed for prediction will get generated in same directory. 
- Make Keil Project in same directory and load the `model.c` file.
- Inculde the header file according to your needs. Naming of the header file is a follows:- `SVM_{kernel name}_{Dataset}.h`
- Build the project and load it into the STM32 Microcontroller.
- Start the debug session and you can see the accuracy using `Watch 1`.

### Contributors

- Sameer Sharma (B21CS066)
- Shalin Jain (B21CS070)