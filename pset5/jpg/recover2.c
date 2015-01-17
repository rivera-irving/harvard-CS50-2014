/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 
 
// TODO


 #include <stdio.h>
 #include <stdlib.h>
 #include <stdint.h>
 #include <stdbool.h>
 #include <string.h>
 
 typedef uint8_t BYTE;
 
 #define BLOCKSIZE 512
 
 int main(int argc, char* argv[])
 {
     // check the command
     if (argc != 2)
     {
         printf("Usage: recover file\n");
         return 1;
     }
     
     FILE* fp = fopen(argv[1], "r");
     
     // check the file availability
     if (fp == NULL)
     {
         printf("%s cannot open\n", argv[1]);
         return 1;
     }
     
     // define a buffer with 512 bytes
     BYTE buffer[BLOCKSIZE];
     
     // define a temp output file
     FILE* outfile = NULL;
     
     // define the jpg count and jpg status
     int jpgcount = 0;
     bool search = true;
     
     // search through the file
     while (search)
     {
         // read the fp into buffer
         for (int i = 0; i < BLOCKSIZE; i++)
         {
             if (feof(fp))
             {
                 fclose(fp);
                 
                 if (outfile != NULL)
                 {
                     fclose(outfile);                     
                     search = false;
                 //summary of the recover process
                 //printf("JPG found: %d\n", jpgcount);
                     return 0;
                 }
             }
             
             fread(&buffer[i], sizeof(BYTE), 1, fp);
         }
         
         // start of a new jpg "0xff 0xd8 0xff 0xe0 || 0xff 0xd8 0xff 0xe1" code         
         if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
         {
             // count the jpg found
             jpgcount++;
             
             // check if there's jpg found before
             if (outfile != NULL)
                 fclose(outfile);
             
             // creat a new jpg file with count number
             char name[4];
             sprintf(name, "%03d.jpg", jpgcount - 1);
              
             // point the outfile to the newly ceated file
             outfile = fopen(name, "w");
                 
             // check if the file can be written
             if(outfile == NULL)
             {
                 printf("Could not write the jpg.\n");
                 return 1;
             }
             
             // write the buffer into the file
             fwrite(&buffer[0], BLOCKSIZE * sizeof(BYTE), 1, outfile);
         }
         else if (outfile != NULL)
         {                 
             // copy the continued data in buffer
             fwrite(&buffer[0], BLOCKSIZE * sizeof(BYTE), 1, outfile);
         }
     }
 }
