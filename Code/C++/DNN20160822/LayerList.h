#include <stdio.h>
#include <vector>
#include "Layer.h" 

#ifndef LayerList_h
#define LayerList_h
class LayerList : public vector<Layer*>{
	private:
	public: 
		void priLayerList();
		void writeLayerListToTxt( string);
		void readTxtToLayerList( string);
};
#endif
