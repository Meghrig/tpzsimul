//
//   Copyright (C) 1998-2011 by Galerna Project, the University of
//   Cantabria, Spain.
//
//   This file is part of the TOPAZ network simulator, originallty developed
//   at the Unviersity of Cantabria
//
//   TOPAZ shares a large proportion of code with SICOSYS which was 
//   developed by V.Puente and J.M.Prellezo
//
//   TOPAZ has been developed by P.Abad, L.G.Menezo, P.Prieto and
//   V.Puente
// 
//  --------------------------------------------------------------------
//
//  If your use of this software contributes to a published paper, we
//  request that you (1) cite our summary paper that appears on our
//  website (http://www.atc.unican.es/topaz/) and (2) e-mail a citation
//  for your published paper to topaz@atc.unican.es
//  
//  If you redistribute derivatives of this software, we request that
//  you notify us and either (1) ask people to register with us at our
//  website (http://www.atc.unican.es/topaz/) or (2) collect registration
//  information and periodically send it to us.
//  
//   --------------------------------------------------------------------
//
//   TOPAZ is free software; you can redistribute it and/or
//   modify it under the terms of version 2 of the GNU General Public
//   License as published by the Free Software Foundation.
//
//   TOPAZ is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//   General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with the TOPAZ simulator; if not, write to the Free Software
//   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
//   02111-1307, USA
//
//   The GNU General Public License is contained in the file LICENSE.
//
//     
//*************************************************************************
//:
//    File: TPZDemultiplexor.cpp
//
//    Class:  TPZDemultiplexor
//
//    Inherited from:  TPZRunnableComponent
// :
//*************************************************************************
//end of header


//
//*************************************************************************



#include <TPZDemultiplexor.hpp>

#ifndef __TPZDemultiplexorFlow_HPP__
#include <TPZDemultiplexorFlow.hpp>
#endif

#ifndef __TPZRouter_HPP__
#include <TPZRouter.hpp>
#endif

#ifndef __TPZConst_H__
#include <TPZConst.hpp>
#endif

//*************************************************************************

IMPLEMENT_RTTI_DERIVED(TPZDemultiplexor,TPZRunnableComponent);

//*************************************************************************
//:
//  f: TPZDemultiplexor (const TPZComponentId & id);
//
//  d:
//:
//*************************************************************************

TPZDemultiplexor :: TPZDemultiplexor(const TPZComponentId& id,
                                     TPZDemuxControl control )
                  : TPZRunnableComponent(id),
		  m_demuxControl(control)
		  
{

}


//*************************************************************************
//:
//  f: ~ TPZDemultiplexor ();
//
//  d:
//:
//*************************************************************************

TPZDemultiplexor :: ~TPZDemultiplexor()
{

}

//*************************************************************************
//:
//  f: virtual void buildFlowControl ();
//
//  d:
//:
//*************************************************************************

void TPZDemultiplexor :: buildFlowControl()
{
   if (getDemuxControl()==TPZDemultiplexor::CT)
   {
      setFlowControl(new TPZDemultiplexorFlow(*this));
   }
   
   if (getFlowControl())
   {
      getFlowControl()->initialize();
   }
   else
   {
      TPZString err;
      err.sprintf(ERR_TPZFIFO_001, getDemuxControl());
      EXIT_PROGRAM(err);
   }
   
}

//*************************************************************************
//:
//  f: virtual TPZString AsString () const;
//
//  d:
//:
//*************************************************************************

TPZString TPZDemultiplexor :: asString() const
{
   TPZString string = getName();
   if( getRouter() )
      string += ((TPZRouter*)getRouter())->getPosition().asString();
   return string;
}


//*************************************************************************
//:
//  f: static TPZDemultiplexor * newFrom (TPZTag const * tag, TPZComponent * owner);
//
//  d:
//:
//*************************************************************************

TPZDemultiplexor* TPZDemultiplexor :: newFrom( const TPZTag* tag, TPZComponent* owner )
{
   TPZComponentId idDemultiplexor(*tag);
   TPZString dmuxOutputs, demuxControl;
   unsigned size;
   
   if( ! (tag->getAttributeValueWithName(TPZ_TAG_OUTPUTS, dmuxOutputs)) )
   {
      TPZString err;
      err.sprintf( ERR_TPZRTING_002, (char*)TPZ_TAG_OUTPUTS );
      EXIT_PROGRAM(err);
   }
   if( ! (tag->getAttributeValueWithName(TPZ_TAG_DEMUX_CONTROL, demuxControl)) )
   {
      TPZString err;
      err.sprintf( ERR_TPZRTING_002, (char*)TPZ_TAG_DEMUX_CONTROL );
      EXIT_PROGRAM(err);
   }
      
   TPZDemuxControl control=TPZDemultiplexor::NIL;
   
   if ( demuxControl==TPZ_TAG_CUTHROUGH)
   {
      control=TPZDemultiplexor::CT;
   }
        
   TPZDemultiplexor* dmux = new TPZDemultiplexor(idDemultiplexor,control);
   dmux->setNumberOfOutputs(dmuxOutputs.asInteger());
   
   return dmux;
}


//*************************************************************************


// end of file