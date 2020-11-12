//#pragma once
//
//#include "Wisdom.h"
//
//namespace SDPsWisdomGenesis{
//	template <class T>
//	class IListener{
//	public:
//		virtual ~IListener<T>() = default;
//		_4_DEFAULTED(IListener<T>)
//
//		virtual static IListener<T>* CreateListener() = 0; //Factory method
//		virtual void OnEvent(const T* const event) = 0;
//	protected:
//		IListener<T>() = default;
//	};
//}