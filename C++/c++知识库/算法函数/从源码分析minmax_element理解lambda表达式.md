### minmax_element函数解析
```cpp
/**
   *  @brief  Determines min and max at once as an ordered pair.                          //从有序列表中一次遍历选取出最小值和最大值
   *  @ingroup sorting_algorithms
   *  @param  __a  A thing of arbitrary type.
   *  @param  __b  Another thing of arbitrary type.
   *  @param  __comp  A @link comparison_functors comparison functor @endlink.
   *  @return A pair(__b, __a) if __b is smaller than __a, pair(__a,
   *  __b) otherwise.
  */
  template<typename _Tp, typename _Compare>
    _GLIBCXX14_CONSTEXPR
    inline pair<const _Tp&, const _Tp&>                                                //两个值进行比较
    minmax(const _Tp& __a, const _Tp& __b, _Compare __comp)
    {
      return __comp(__b, __a) ? pair<const _Tp&, const _Tp&>(__b, __a)
			      : pair<const _Tp&, const _Tp&>(__a, __b);
    }

  template<typename _ForwardIterator, typename _Compare>                                //从一组有序列表中取出一对值
    _GLIBCXX14_CONSTEXPR
    pair<_ForwardIterator, _ForwardIterator>
    __minmax_element(_ForwardIterator __first, _ForwardIterator __last,
		     _Compare __comp)
    {
      _ForwardIterator __next = __first;
      if (__first == __last
	  || ++__next == __last)
	return std::make_pair(__first, __first);

      _ForwardIterator __min{}, __max{};                                                //c++11 在变量后加初始化列表{}
      if (__comp(__next, __first))
	{
	  __min = __next;
	  __max = __first;
	}
      else
	{
	  __min = __first;
	  __max = __next;
	}

      __first = __next;
      ++__first;

      while (__first != __last)
	{
	  __next = __first;
	  if (++__next == __last)
	    {
	      if (__comp(__first, __min))
		__min = __first;
	      else if (!__comp(__first, __max))
		__max = __first;
	      break;
	    }

	  if (__comp(__next, __first))                    //  next 和 first比较，小的有可能是最小值，大的有可能是最大值         
	    {
	      if (__comp(__next, __min))
		__min = __next;
	      if (!__comp(__first, __max))
		__max = __first;
	    }
	  else
	    {
	      if (__comp(__first, __min))
		__min = __first;
	      if (!__comp(__next, __max))
		__max = __next;
	    }

	  __first = __next;                               //first 和 next 是双“指针”
	  ++__first;
	}

      return std::make_pair(__min, __max);
    }
```

通常这个 __comp()函数在调用的时候通过lambda表达式给出

### lambda 表达式
```cpp
[capture list] (parameter list) -> return type{function body}
```
捕获列表是一个 lambda 表达式**所在函数中定义的局部变量**的列表，通常为空。
lambda 和普通函数不同，必须使用**尾置返回**来指定返回类型。
我们可以忽略参数列表和返回类型，但必须包括**捕获列表**和**函数体**。

示例：
```cpp
auto min_max = minmax_element(matches.begin(), matches.end(),
                                [](const DMatch &m1, const DMatch &m2) { return m1.distance < m2.distance; });
```
其中捕获参数为空表示 lambda 表达式不用到所在函数的局部变量，返回类型没有给定，则从函数体中判断是一个 bool 类型。