#include <stdio.h>
#include <stdlib.h>
#include "tomasulo.h"


void writeresultbookkeeping(int RS, int i)
{
	if(Add1.Qj == RS)
	{
		Add1.Vj = instrQ[i].Result;
		Add1.Qj = 0;
	}
	if(Add1.Qk == RS)
	{
		Add1.Vk = instrQ[i].Result;
		Add1.Qk = 0;
	}
	if(Mult1.Qj == RS)
	{
		Mult1.Vj = instrQ[i].Result;
		Mult1.Qj = 0;
	}
	if(Mult1.Qk == RS)
	{
		Mult1.Vk = instrQ[i].Result;
		Mult1.Qk = 0;
	}
	if(Div1.Qj == RS)
	{
		Div1.Vj = instrQ[i].Result;
		Div1.Qj = 0;
	}
	if(Div1.Qk == RS)
	{
		Div1.Vk = instrQ[i].Result;
		Div1.Qk = 0;
	}
}


void simulateTomasulo()
{
	int i = 0;
  int writeresult_count = 0;
	int clockcycle = 1;
	int terminatesin = 0;
  int issue_count = 0;
	while(!terminatesin)
	{

		//issuebookkeeping
      if(instrCount > issue_count)
      {
        i = issue_count;
        if(instrQ[i].instrType == MULT)
			  {
          if(Mult1.busy == 0)
          {                                             // check issue
            instrQ[i].Issue = clockcycle;              // recording time
                                                      // book issuebookkeeping
            if(Qi[instrQ[i].S1] != 0)
            {
            	Mult1.Qj = Qi[instrQ[i].S1];
            }
            else
            {
            	Mult1.Vj = Regs[instrQ[i].S1];
            	Mult1.Qj = 0;
            }
            if(Qi[instrQ[i].S2] != 0)
            {
            	Mult1.Qk = Qi[instrQ[i].S2];
            }
            else
            {
            	Mult1.Vk = Regs[instrQ[i].S2];
            	Mult1.Qk = 0;
            }
            Qi[instrQ[i].D] = MULT1;
            Mult1.busy = 1;
            issue_count = issue_count + 1;
				     }
           }
			     if(instrQ[i].instrType == ADD)
			     {
             if(Add1.busy == 0)
             {                                          // check
                instrQ[i].Issue = clockcycle;          // recording time
                                                      // book issuebookkeeping
                if(Qi[instrQ[i].S1] != 0)
          			{
          				Add1.Qj = Qi[instrQ[i].S1];
          			}
          			else
          			{
          				Add1.Vj = Regs[instrQ[i].S1];
          				Add1.Qj = 0;
          			}
          			if(Qi[instrQ[i].S2] != 0)
          			{
          				Add1.Qk = Qi[instrQ[i].S2];
          			}
          			else
          			{
          				Add1.Vk = Regs[instrQ[i].S2];
          				Add1.Qk = 0;
          			}
          			Qi[instrQ[i].D] = ADD1;
          			Add1.busy = 1;
                issue_count = issue_count + 1;
				      }
           }
           if(instrQ[i].instrType == SUB)
			     {
             if(Add1.busy == 0)
             {                                          // check
                instrQ[i].Issue = clockcycle;          // recording time
                                                      // book issuebookkeeping
                if(Qi[instrQ[i].S1] != 0)
          			{
          				Add1.Qj = Qi[instrQ[i].S1];
          			}
          			else
          			{
          				Add1.Vj = Regs[instrQ[i].S1];
          				Add1.Qj = 0;
          			}
          			if(Qi[instrQ[i].S2] != 0)
          			{
          				Add1.Qk = Qi[instrQ[i].S2];
          			}
          			else
          			{
          				Add1.Vk = Regs[instrQ[i].S2];
          				Add1.Qk = 0;
          			}
          			Qi[instrQ[i].D] = ADD1;
          			Add1.busy = 1;
                issue_count = issue_count + 1;
				      }
           }
           if(instrQ[i].instrType == DIV)
			     {
             if(Div1.busy == 0)
             {                                          // check
                instrQ[i].Issue = clockcycle;          // recording time
                                                      // book issuebookkeeping
                if(Qi[instrQ[i].S1] != 0)
          			{
          				Div1.Qj = Qi[instrQ[i].S1];
          			}
          			else
          			{
          				Div1.Vj = Regs[instrQ[i].S1];
          				Div1.Qj = 0;
          			}
          			if(Qi[instrQ[i].S2] != 0)
          			{
          				Div1.Qk = Qi[instrQ[i].S2];
          			}
          			else
          			{
          				Div1.Vk = Regs[instrQ[i].S2];
          				Div1.Qk = 0;
          			}
          			Qi[instrQ[i].D] = DIV1;
          			Div1.busy = 1;
                issue_count = issue_count + 1;
				      }
           }
    }


    // execute

    for(int i = 0; i < instrCount; i++)
		{
			if(instrQ[i].instrType == ADD)
			{
				if(instrQ[i].Issue != 0 && clockcycle > instrQ[i].Issue  && instrQ[i].ExecStart == 0 && Add1.Qj == 0 && Add1.Qk == 0)
				{
					instrQ[i].ExecStart = clockcycle;
					instrQ[i].ExecComp = instrQ[i].ExecStart + ADD_CLOCKS - 1;
				}
			}
       else if(instrQ[i].instrType == MULT)
			{
				if(instrQ[i].Issue != 0 && clockcycle > instrQ[i].Issue  && instrQ[i].ExecStart == 0 && Mult1.Qj == 0 && Mult1.Qk == 0)
				{
					instrQ[i].ExecStart = clockcycle;
					instrQ[i].ExecComp = instrQ[i].ExecStart + MULT_CLOCKS - 1;

				}
			}
      else if(instrQ[i].instrType == SUB)
     {
       if(instrQ[i].Issue != 0 && clockcycle > instrQ[i].Issue  && instrQ[i].ExecStart == 0 && Add1.Qj == 0 && Add1.Qk == 0)
       {
         instrQ[i].ExecStart = clockcycle;
         instrQ[i].ExecComp = instrQ[i].ExecStart + ADD_CLOCKS - 1;
       }
     }
     else if(instrQ[i].instrType == DIV)
    {
      if(instrQ[i].Issue != 0 && clockcycle > instrQ[i].Issue  && instrQ[i].ExecStart == 0 && Div1.Qj == 0 && Div1.Qk == 0)
      {
        instrQ[i].ExecStart = clockcycle;
        instrQ[i].ExecComp = instrQ[i].ExecStart + DIV_CLOCKS - 1;
      }
    }
  }

    // write result

    for(i = 0; i < instrCount; i++)
  	{

  		if(instrQ[i].ExecComp != 0 && clockcycle > instrQ[i].ExecComp && instrQ[i].instrType == ADD && instrQ[i].WriteRes == 0)
  		{
  			instrQ[i].WriteRes = clockcycle;
        if(Qi[instrQ[i].D] == ADD1)
  			{
  				Regs[instrQ[i].D] = instrQ[i].Result;
  				Qi[instrQ[i].D] = 0;
  			}
  			writeresultbookkeeping(ADD1, i);
        Add1.busy = 0;
        writeresult_count = writeresult_count + 1;
        break;
  		}

     else if(instrQ[i].ExecComp != 0 && clockcycle > instrQ[i].ExecComp && instrQ[i].instrType == MULT && instrQ[i].WriteRes == 0)
  		{
        instrQ[i].WriteRes = clockcycle;
  			if(Qi[instrQ[i].D] == MULT1)
  			{
  				Regs[instrQ[i].D] = instrQ[i].Result;
  				Qi[instrQ[i].D] = 0;
  			}

  			writeresultbookkeeping(MULT1, i);
        Mult1.busy = 0;
        writeresult_count = writeresult_count + 1;
        break;
  		}
      else if(instrQ[i].ExecComp != 0 && clockcycle > instrQ[i].ExecComp && instrQ[i].instrType == SUB && instrQ[i].WriteRes == 0)
   		{
         instrQ[i].WriteRes = clockcycle;
   			if(Qi[instrQ[i].D] == ADD1)
   			{
   				Regs[instrQ[i].D] = instrQ[i].Result;
   				Qi[instrQ[i].D] = 0;
   			}

   			writeresultbookkeeping(ADD1, i);
         Add1.busy = 0;
         writeresult_count = writeresult_count + 1;
         break;
   		}
      else if(instrQ[i].ExecComp != 0 && clockcycle > instrQ[i].ExecComp && instrQ[i].instrType == DIV && instrQ[i].WriteRes == 0)
   		{
         instrQ[i].WriteRes = clockcycle;
   			if(Qi[instrQ[i].D] == DIV1)
   			{
   				Regs[instrQ[i].D] = instrQ[i].Result;
   				Qi[instrQ[i].D] = 0;
   			}

   			writeresultbookkeeping(DIV1, i);
         Div1.busy = 0;
         writeresult_count = writeresult_count + 1;
         break;
   		}
    }
//check termination


		if(instrCount == writeresult_count)
		{
			terminatesin = 1;
		}
		clockcycle++;
  }
}



int main(int argc, char **argv)
{
	int i;

	/* Check for the appropriate number of arguments */
	if(argc < 2)
	{
	  printf("Usage: tomasulo inputFile\n");
	  exit(-1);
	}

	/* Read instructions into the instruction queue */
	if((instrCount = readInstructions(argv[1])) < 0)
	{
		exit(-1);
	}
	printf("%d instructions read\n", instrCount);

	/* Initialize Tomasulo algorithm */
	initTomasulo();

	/* Simulate Tomasulo algorithm */
	simulateTomasulo();

	/* Print the Instruction Queue */
	printInstructions();

}
