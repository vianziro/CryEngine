#include "StdAfx.h"
#include "Nodes\G2FlowBaseNode.h"
#include "Global.h"

class CFlowMouseEntity : public CFlowBaseNode<eNCT_Instanced>
{   
public:

   CFlowMouseEntity(SActivationInfo* pActInfo)
   {
	   pActInfo->pGraph->SetRegularlyUpdated(pActInfo->myID,true);
   }
   ~CFlowMouseEntity() {}

   void GetMemoryUsage(ICrySizer * s) const {}



   /*enum EInputPorts
   {
   };*/


   enum EOutputPorts
   {
	   EOP_Activate = 0,
	   EOP_EntityID,
	   EOP_3DMousePosition,
	   EOP_SaidSelect,
	   EOP_SaidGoToDestination,
	   EOP_SaidStop,
	   EOP_SaidContinue,
   };

   virtual void GetConfiguration(SFlowNodeConfig& config)
   {
      static const SInputPortConfig inputs[] =
      {
		  InputPortConfig_Void("Start Simulation",_HELP("this will start simulation")),
          {0},
      };

	  /*static const SOutputPortConfig outputs[] =
      {
		OutputPortConfig_Void("Activate", _HELP("Outputs A Trigger Signal when we right click")),
		OutputPortConfig<EntityId>("EntityID", _HELP("Outputs the EntityId of the currently selected Entity when we left click")),
		OutputPortConfig<Vec3>("3DMousePosition", _HELP("Outputs the 3D Mouse Position of the Mouse when we right Click")),
		{0},
      };*/

      config.pInputPorts = inputs;
	  //config.pOutputPorts = outputs;
      config.sDescription = _HELP("Holds the EntityId of the currently selected Entity and outputs data based on Mouse Events");
      config.SetCategory(EFLN_APPROVED);
   }

   virtual void GetMemoryStatistics(ICrySizer *s)
   {
      s->Add(*this);
   }

   IFlowNodePtr Clone(SActivationInfo* pActInfo)
   {
      return new CFlowMouseEntity(pActInfo);
   }

   virtual void ProcessEvent(EFlowEvent event, SActivationInfo *pActInfo)
   {
      switch(event)
      {
      case eFE_Activate:
         {
            
		 }
		 break;

		 case eFE_Update:
         {
			 
			 /*//checks if there is a valid entity selected and if so then continue
			 if (g_EntityIdUnderMouse != 0)
			 {
				//checks if we just left clicked and if so then send mouse 3d position and trigger signal
				if (g_LeftClicked)
				{
					//send EntityId on left click as well as it appears that when they actually reach their destination the AI:GoTo node looses which entity it was supposed to move
					ActivateOutput(pActInfo, EOP_EntityID, g_EntityIdUnderMouse);
					ActivateOutput(pActInfo, EOP_3DMousePosition, g_RigthClick3dPosition);
					ActivateOutput(pActInfo, EOP_Activate, 1);

					//set Back to false because we only want it true at th exact time we Right click
					g_LeftClicked = false;
				}
				
				//checks if we just right clicked and if so send the entity id if the currently selected entity
				if (g_RightClicked)
				{
					ActivateOutput(pActInfo, EOP_EntityID, g_EntityIdUnderMouse);

					//set Back to false because we only want it true at th exact time we right click
					g_RightClicked = false;
				}


			 }*/
		 }
		 break;

      }
   }

};


// Register the flow node with the name "Stopwatch" in the "MyFlowNodes" section
// Use the Node class for the stopwatch
REGISTER_FLOW_NODE("MyFlowNodes:MouseEntity", CFlowMouseEntity);