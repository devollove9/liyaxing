
/***********************************************************************/ 
/*  Declarations for Project #9                                        */
/***********************************************************************/ 


struct player
{
  unsigned short number;    /* player's jersey number (key) */
  char name[20];            /* player's name                */
  unsigned short games;     /* number of games played       */
  unsigned short goals;     /* number of goals scored       */
  unsigned short assists;   /* number of assists scored     */
  unsigned short points;    /* points (goals + assists)     */
  float points_per_game;    /* points per game played       */
};


struct table
{
  unsigned short capacity;  /* number of elements in table  */
  unsigned short count;     /* number of players in table   */
  struct player* memory;    /* pointer to array of players  */
};


/***********************************************************************/
/*  Function:  search                                                  */
/*                                                                     */
/*  Purpose:  locate and return a pointer to a player, if the          */
/*  player is present in the table.                                    */
/*                                                                     */
/*  Arguments:                                                         */
/*    pointer to table of players                                      */
/*    jersey number of player to be located                            */
/*    pointer to pointer to player                                     */
/*                                                                     */
/*  Return value:                                                      */
/*    1 (true) if player located, 0 (false) otherwise                  */
/***********************************************************************/
 
int search( struct table*, unsigned long, struct player** );


/***********************************************************************/
/*  Function:  delete                                                  */
/*                                                                     */
/*  Purpose:  delete a player from the table, if the                   */
/*  player is present in the table.                                    */
/*                                                                     */
/*  Arguments:                                                         */
/*    pointer to table of players                                      */
/*    jersey number of player to be deleted                            */
/*                                                                     */
/*  Return value:                                                      */
/*    1 (true) if player deleted, 0 (false) otherwise                  */
/***********************************************************************/
 
int delete( struct table*, unsigned long );
 

/***********************************************************************/
/*  Function:  insert                                                  */
/*                                                                     */
/*  Purpose:  insert a player into the table, as long as there is      */
/*  room in the table and the player is not already present.           */ 
/*                                                                     */
/*  Arguments:                                                         */
/*    pointer to table of players                                      */
/*    jersey number of player to be inserted                           */
/*    pointer to name of player                                        */
/*    number of games played                                           */
/*    number of goals scored                                           */
/*    number of assists scored                                         */
/*                                                                     */
/*  Return value:                                                      */
/*    1 (true) if player inserted, 0 (false) otherwise                 */
/***********************************************************************/
 
int insert( struct table*, unsigned long, char*, int, int, int );
 
