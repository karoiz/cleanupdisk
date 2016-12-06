/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* Public macros -------------------------------------------------------------*/
#define NR_OF_TAB_ELEMENTS  ( 1024 * 1024 )  // 1 MB

/* Private types -------------------------------------------------------------*/
typedef uint8_t element_t;

typedef struct {
  element_t* data;
  uint32_t   size;
} buffer_t;

/* Private variables ---------------------------------------------------------*/
static buffer_t b = { 0 };

/* Private functions ---------------------------------------------------------*/

static void buffer_start( void )
{
  b.size = NR_OF_TAB_ELEMENTS * sizeof( element_t );

  b.data = malloc( b.size );

  if ( NULL == b.data )
  {
    exit( EXIT_FAILURE );
  }

  for ( uint32_t count = 0; count < b.size; count++ )
  {
    b.data[ count ] = 0xff;
  }
}

/* ---------------------------------------------------------------------------*/

static void buffer_stop( void )
{
  b.size = 0;

  free( b.data );
  b.data = NULL;
}

/* ---------------------------------------------------------------------------*/

static bool create_file( uint32_t nrFile, uint32_t nrOfMegabytes )
{
  char filename[ 128 ];

  snprintf( filename, sizeof( filename ), "ff_%06d.dat", nrFile );
  printf( "Creating a file %s\n", filename );

  FILE* h = fopen( filename, "w" );

  for ( uint32_t count = 0; nrOfMegabytes > count; count++ )
  {
    if ( b.size != fwrite( b.data, sizeof( element_t ), NR_OF_TAB_ELEMENTS, h ) )
    {
      return false;
    }
  }

  fclose( h );

  return true;
}

/* ---------------------------------------------------------------------------*/

static void remove_file( uint32_t nrFile )
{
  char filename[ 128 ];

  snprintf( filename, sizeof( filename ), "ff_%06d.dat", nrFile );
  printf( "Deleting a file %s\n", filename );

  remove( filename );
}

/* Public functions ----------------------------------------------------------*/

int main( int argc, char* argv[] )
{
  uint32_t countGiga = 0;

  buffer_start();

  for ( ; ; )
  {
    if ( !create_file( countGiga, 1024 ) )
    {
      break;
    }

    countGiga++;
  }

  buffer_stop();

  do
  {
    remove_file( countGiga );
  }
  while ( countGiga-- );

  return EXIT_SUCCESS;
}
