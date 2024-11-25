# 实验

### 实验二 Demeer5（kick 和dash） 

**1、试验目的:**  

1. 了解Demeer5的工作原理  
2. 会对Demeer5进行简单的修改 

**2、试验设备**

硬件环境：PC

软件环境：Linux 

**3、试验内容** 

（1）Demeer5的工作原理:
Demeer5函数是整个球队的核心，它最终返回一个可以执行的动作，底层的模块负责将 此动作发送给server，然后由server执行。可以说，Demeer5就是我们想法的体现，是一支 球队的大脑。在Demeer5中有一系列的判断来决定每个周期的动作。下面对Demeer5进行简要的分析.  Demeer5( )是一个决策函数，在策略上使用的是下面这个简单的策略：  如果球可踢，则用最大力量踢球；  如果球不可踢且我是队友中最快到球的队员，则去截球；  其他情况按战略点跑位。  我们现在只要看一下球可踢时的代码：

```

if (WM->isBallKickable())
{
    // 如果球可踢
    // 确定踢向的点
    VecPosition posGoal(PITCH_LENGTH / 2.0,
                        (-1 + 2 * (WM->getCurrentCycle() % 2)) * 0.4 * SS->getGoalWidth());
    // 调用踢球的动作
    soc = kickTo(posGoal, SS->getBallSpeedMax()); // kick maximal
                                                  // 将动作放入命令队列中
    ACT->putCommandInQueue(soc);
    // 将脖子转向球
    ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
    // 记录调试信息
    Log.log(100, "kick ball");
}

```

这一小段函数决定了当球在球员Agent的可踢范围之内时应当做的动作，这里是一个简单的 把球向前踢而不考虑任何其他情况的方法。该程序段的条理是很清晰的。

（2）对Demeer5进行简单的修改：
现在我们对Demeer5进行简单的修改，让它在球可踢的时候进行带球的动作。带球就 是kick和dash动作序列的结合。带球的函数在BasicPlayer中，函数为dribble（）。它接收两个参数，第一个参数为带球的方向，第二个参数为带球的类型。  带球类型解释如下： 

```

DRIBBLE_FAST：快速带球； 
DRIBBLE_SLOW：慢速带球； 
DRIBBLE_WITHBALL：安全带球；

```

所以，对dribble的一种调用形式为：dribble（ang，DRIBBLE_FAST ）  其中ang为AngDeg（是一个double）类型该函数的返回值是一个SoccerCommand类型。  知道了如何调用dribble，我们来对Demeer5进行替换： 

```

if (WM->isBallKickable())
{
    AngDeg ang = 0.0;
    soc = dribble（ang，DRIBBLE_FAST ）; // 进行带球
                                         // 将动作放入命令队列中
    ACT->putCommandInQueue(soc);
    // 将脖子转向球
    ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
    // 记录调试信息
    Log.log(100, "kick ball");
}

```

这样，在球可踢的时候，球员Agent将把球带向前方，这里取的是0度角，即沿x轴一直向 前快速带球。  我们再次对Demeer5函数进行修改，这次是让球员Agent将球踢向各个不同的地方。 这将调用kickTo（）函数来完成。下面简要说明一下kickTo（）函数的使用方法：这个函数有两个参数，第一个参数是目标点的坐标，第二个参数是球到达目标点是的速度，返回一个踢球的动作。可以使用下面的形式来调用：

```

VecPosition pos(x, y);
double speed = 1.0;
kickTo(pos, speed);

```

kickTo()函数在其内部将会决定踢球时所用力量的大小，并且会判断是否能够将球踢到该点， 并作出相应的调整。比如，将球一直踢向( 0， 0)点, 1.0的末速度：

```

else if (WM->isBallKickable())
{
    soc = kickTo(VecPosition(0, 0), 1.0);
    // 将动作放入命令队列中
    ACT->putCommandInQueue(soc);
    // 将脖子转向球
    ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
    // 记录调试信息
    Log.log(100, "kick ball");
}

```

- 根据上述操作，完成以下踢球操作：

- 将球踢向对方的球门。

  ```
  
  else if (WM->isBallKickable()) // 如果球已知，而且当前球在我脚下(可踢)
  {
      VecPosition pos = (PITCH_LENGTH / 2.0, (-1 + 2 * (WM->getCurrentCycle() % 2)) *
                                                 0.4 * SS->getGoalWidth()); // 得到对方球门的坐标
      soc = kickTo(pos, SS->getBallSpeedMax());
      ACT->putCommandInQueue(soc);
      ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
  }
  
  ```

- 将球踢向距离自己最近的队友。 

```

else if (WM->isBallKickable()) // 如果球已知，而且当前球在我脚下(可踢)
{
    VecPosition vec = WM->globalPosition(WM->getClosestInSetTo(OBJECT_SET_TEAMMATES, posAgent));
    soc = kickTo(vec, 2.0);
    ACT->putCommandInQueue(soc);
    ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
}

```

- 尝试不同的踢球点。

```

else if (WM->isBallKickable())
// if kickable 如果球已知，而且当前球在我脚下(可踢) 那么就射门
{
    // 尝试不同的踢球点（3) 踢向Flag center bottom
    VecPosition posCB = WM->getGlobalPosition(OBJECT_FLAG_C_B);
    soc = kickTo(posCB, SS->getBallSpeedMax());                 // 以最大速度
    ACT->putCommandInQueue(soc);                                // 放入命令队列 一个周期可以做很多动作 把这些动作放在一个队列中 一起发给服务器
    ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc)); // 把脖子转向球，也就是一直看着球
    Log.log(100, "kick ball");                                  // 记录调试信息
}

```

以下是一些可能用到的函数：
1．得到对方球门的坐标
`VecPosition  getPosOpponentGoal();` 
调用：`WM-> getPosOpponentGoal ();` 
2．得到距离自己最近的队员
`ObjectT  getClosestInSetTo( );`  
调用：`WM->getClosestInSetTo(OBJECT_SET_TEAMMATES，posAgent )` 
3、得到一个对象的坐标
`VecPosition  getGlobalPosition( ObjectT o )`
调用：`WM->getGlobalPosition( o );`
更多的函数请查找教材，或者查看源程序的`WorldModel.cpp`, `WorldModelHighLevel.cpp`, `WorldModelPredict.cpp` 等文件。

- 根据上述内容，完成以下带球的操作
- 用不同的带球模式进行带球，并观察效果，比较异同。

```
    
    dribble(vec, DRIBBLE)
    DRIBBLE_FAST 快速带球
    DRIBBLE_SLOW 慢速带球
    DRIBBLE_WITHBALL 安全带球的模式带球
    
```

- 将球向对方的球门方向带。

```

else if (WM->isBallKickable())
{
    AngDeg ang = 0.0;
    soc = dribble(ang, DRIBBLE_FAST);
    ACT->putCommandInQueue(soc);
    ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
}

```

- 尝试不同的带球组合。

```

else if (WM->isBallKickable())
{
    if (WM->isInTheirPenaltyArea(WM->getBallPos()))
    {
        VecPosition pos = (PITCH_LENGTH / 2.0, (-1 + 2 * (WM->getCurrentCycle() % 2)) *
                                                   0.4 * SS->getGoalWidth());
        soc = kickTo(pos, SS->getBallSpeedMax());
    }
    else
    {
        AngDeg ang = 0.0;
        soc = dribble(ang, DRIBBLE_FAST);
    }
    AngDeg ang = 0.0;
    soc = dribble(ang, DRIBBLE_FAST);
    ACT->putCommandInQueue(soc); // 放入命令队列
    ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
}

```

- 根据上述内容，完成以下综合联系：
  带球与踢球的结合：
  让 agent 一直向对方球门的方向带球，在进入对方禁区后以最大力量踢向球门( 末速度最大为 2.7 )。涉及到的具体函数请查看教材。

  ```
  
  else if (WM->isBallKickable())
  // if kickable 如果球已知，而且当前球在我脚下(可踢) 那么就射门
  {
      VecPosition posGoal(PITCH_LENGTH / 2.0,
                          (-1 + 2 * (WM->getCurrentCycle() % 2)) * 0.4 * SS->getGoalWidth()); // 获取对方球门坐标
  
      if (WM->isInTheirPenaltyArea(WM->getBallPos())) // 判断是否在禁区范围内
      {
          soc = kickTo(posGoal, 2.7); // 以最大力量踢向球门
      }
      else
      {
          AngDeg ang = (posGoal - posAgent).getDirection(); // 获取对方球门方向
          soc = dribble(ang, DRIBBLE_FAST);                 // 向对方球门带球
      }
      ACT->putCommandInQueue(soc);                                // 放入命令队列 一个周期可以做很多动作 把这些动作放在一个队列中 一起发给服务器
      ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc)); // 把脖子转向球，也就是一直看着球
      Log.log(100, "kick ball");                                  // 记录调试信息
  }
  
  ```
  

### 实验三 Demeer5 的基本动作

**1.实验目的**

熟悉demeer5并学会demeer5的基本使用方法，具体内容如下：

（1） 能理解UVA程序中原来的demeer5中的内容

（2） 能通过修改demeer5中的具体函数内容实现对场上球员的控制

（3） 能通过底层动作的简单组合控制场上队员做出一些复杂动作

**2、实验设备**

硬件环境：PC机

软件环境：操作系统Linux

**3. 实验内容及步骤**

（1） 在球队程序中找到player.c并打开（03版本的程序，打开playerTeams.c）;

（2） 在player.c中找到Demmer5函数;

（3） 阅读此段程序，并结合Monitor观察球员的具体行为（你将发现可以踢到球的球员会将球朝球门的方向踢去，而不能踢到球的队员中如果是离球最近的队员就去截球，否者则按阵型跑位）;

（4） 修改Demmer5函数改变队员的行为具体步骤如下：

1. 在demeer5函数中找到

   ```
   
   if (WM->isBallKickable())
   // isBallKickable()函数用来判断球是否可踢
   {
   	VecPosition posGoal(PITCH_LENGTH / 2.0,
   						(-1 + 2 * (WM->getCurrentCycle() % 2)) * 0.4 * SS->getGoalWidth());
   	// 设定射门位置坐标
   	soc = kickTo(posGoal, SS->getBallSpeedMax()); // 朝球门方向将球以最大力度踢出
   	ACT->putCommandInQueue(soc); // 只有把命令放入命令队列动作才会执行 ACT->putCommandInQueue( turnNeckToObject( OBJECT_BALL, soc ) );
   	// 做动作的同时改变脖子的方向
   }
   
   ```

2. 『控球』将此函数修改为

   ```
   
   if (WM->isBallKickable())
   {
   	soc = kickBallCloseToBody(45);
   	ACT->putCommandInQueue(soc);
   	ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
   }
   
   ```

   然后编译运行程序，观察球员的行为我们会发现当球可踢时，球员不再朝着球门的方向踢了，而是将球绕自己身体转动（uva的这个底层动作经常把球转丢!）

3. 『带球』将此函数修改为

   ```
   
   if (WM->isBallKickable())
   {
   	soc = dribble(0.0, DRIBBLE_SLOW); // 其中dribble函数中第一个参数表示带球的方向
   	-180 ~180之间，不一定是0.0 ACT->putCommandInQueue(soc);
   	ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
   }
   
   ```

   然后编译运行程序，观察球员的行为我们会发现当球可踢时，球员不再朝着球门的方向踢了，而是朝我们指定的方向执行带球。

4. 『传球』将此函数修改为

   ```
   
   if (WM->isBallKickable())
   {
   	soc = leadingPass(OBJECT_TEAMMATE_9，1);
   	// 其中leadingPass中第一个参数表示传球的对象,本实验中我们将球直接传给指定号码（1 ~11）的球员, 不一定是OBJECT_TEAMMATE_9
   	ACT->putCommandInQueue(soc);
   	ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
   }
   
   ```

   然后编译运行程序，观察球员的行为我们会发现当球可踢时，球员不再朝着球门的方向踢了，而是将球传给我们指定号码的队员。

5. 『配合』将此函数修改为

   ```
   
   if (WM->isBallKickable())
   {
   	if (WM->getAgentObjectType() == OBJECT_TEAMMATE_9)
   		soc = dribble(0.0, DRIBBLE_SLOW);	 // 带球 else
   	soc = leadingPass(OBJECT_TEAMMATE_9，1); // 传球 ACT->putCommandInQueue( soc );
   	ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
   }
   
   ```

   编译程序，观察球员行为，会发现，当9号队员得到球后会朝前方带球，其他队员得到球后会将球传给9号（不管9号是不是越位）。

根据以上描述完成练习：通过基本动作的组合实现球员的以下行为（1，2题希望大家仔细思考一下，第3题有兴趣的同学可以思考一下，更多基本动作请查阅BasicPlayer.c函数,或其他有关书籍,也希望大家能做出更多的动作来）。

- 如果在对方禁区内就射门，否则，如果是7，8，9号队员就朝前带球，其他队员将球传给9号（用`WM->isInTheirPenaltyArea(WM->getBallPos())`来判断球是否在对方禁区）

  ```
  
  else if (WM->isBallKickable())
  // if kickable 如果球已知，而且当前球在我脚下(可踢) 那么就射门
  {
  	VecPosition posGoal(PITCH_LENGTH / 2.0,
  						(-1 + 2 * (WM->getCurrentCycle() % 2)) * 0.4 * SS->getGoalWidth()); // 获取对方球门坐标
  
  	if (WM->isInTheirPenaltyArea(WM->getBallPos())) // 判断是否在禁区范围内
  	{
  		soc = kickTo(posGoal, SS->getBallSpeedMax()); // 以最大力量踢向球门
  	}
  	else
  	{
  		if (WM->getAgentObjectType() == OBJECT_TEAMMATE_7 || WM->getAgentObjectType() == OBJECT_TEAMMATE_8 || WM->getAgentObjectType() == OBJECT_TEAMMATE_9)
  		{
  			soc = dribble(0.0, DRIBBLE_FAST);
  		}
  		else
  		{
  			soc = leadingPass(OBJECT_TEAMMATE_9, 1.0);
  		}
  	}
  	AngDeg ang = (posGoal - posAgent).getDirection();			// 获取对方球门方向
  	soc = dribble(ang, DRIBBLE_FAST);							// 向对方球门带球
  	ACT->putCommandInQueue(soc);								// 放入命令队列 一个周期可以做很多动作 把这些动作放在一个队列中 一起发给服务器
  	ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc)); // 把脖子转向球，也就是一直看着球
  	Log.log(100, "kick ball");									// 记录调试信息
  }
  
  ```

  

- 如果队员的位置在自己半场就将球朝对方球门踢去，否者就朝前方带球（用 `WM->getBallPos().getX()`来得到球的x坐标）

  ```
  
  else if (WM->isBallKickable())
  // if kickable 如果球已知，而且当前球在我脚下(可踢) 那么就射门
  {
  	if (WM->getBallPos().getX() < 0)
  	{
  		VecPosition posGoal(PITCH_LENGTH / 2.0,
  							(-1 + 2 * (WM->getCurrentCycle() % 2)) * 0.4 * SS->getGoalWidth());
  		soc = kickTo(posGoal, SS->getGoalWidth());
  	}
  	else
  	{
  		soc = dribble(0.0, DRIBBLE_FAST);
  	}
  	ACT->putCommandInQueue(soc);								// 放入命令队列 一个周期可以做很多动作 把这些动作放在一个队列中 一起发给服务器
  	ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc)); // 把脖子转向球，也就是一直看着球
  	Log.log(100, "kick ball");									// 记录调试信息
  }
  
  ```

- 当有人来抢球时（离自己很近），就将球传给离自己最近的队员，否则就自己带球(调用`WM->getClosestRelativeInSet`函数来得到离自己最近的己方或对方球员，通过 `pos1.getDistanceTo(pos2)`来得到两位置之间的距离)。

  ```
  
  else if (WM->isBallKickable())
  // if kickable 如果球已知，而且当前球在我脚下(可踢) 那么就射门
  {
  	Circle cir = Circle(WM->getAgentGlobalPosition(), 2.5); // 以自身为圆心，半径为2.5的圆
  	int Num = WM->getNrInSetInCircle(OBJECT_SET_OPPONENTS, cir);
  	if (Num >= 1) // 如果该圆内有敌人表示有人抢球
  	{
  		VecPosition posTeam = WM->getGlobalPosition(WM->getClosestInSetTo(OBJECT_SET_TEAMMATES, posAgent)); // 获取离自己最近的队友的坐标
  		VecPosition posOpponent = WM->getGlobalPosition(WM->getClosestInSetTo(OBJECT_SET_OPPONENTS, posAgent));
  		if (posAgent.getDistanceTo(posTeam) <= posAgent.getDistanceTo(posOpponent)) // 如果队友比对手近
  		{
  			soc = kickTo(posTeam, SS->getBallSpeedMax()); // 传给队友
  		}
  		else // 如果对手比队友近
  		{
  			AngDeg ang = (posAgent - posOpponent).getDirection(); // 踢向对手的反方向
  			soc = dribble(ang, DRIBBLE_FAST);
  		}
  	}
  	else // 若该范围内没有敌人 表示没人抢球
  	{
  		dribble(0.0, DRIBBLE_FAST);
  	}
  	ACT->putCommandInQueue(soc);								// 放入命令队列 一个周期可以做很多动作 把这些动作放在一个队列中 一起发给服务器
  	ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc)); // 把脖子转向球，也就是一直看着球
  	Log.log(100, "kick ball");									// 记录调试信息
  }
  
  ```


### 实验四 复杂的动作决策

**1. 实验目的**

进一步了解demeer5并能熟悉的修改demeer5的内容以达到对场上的球员的控制

(1) 能理解 UVA 程序中原来的 demeer5 中的全部内容

(2) 能通过修改 demeer5 中的具体函数内容实现对场上球员的控制

(3) 能通过底层动作的简单组合控制场上队员做出一些复杂动作决策

(4) 对 WorldModel 有初步的认识，学会在 WorldModel,basicplayer 里添加新函

**2. 实验设备**

硬件环境：PC机

软件环境：操作系统Linux

**实验内容**

- 任务一：判断守门员的位置，朝球门空隙较大的一方射门，（通过在WorldModel里建立新状态来判断，球门哪一方空隙较大，守门员的位置为VecPosition posGoalie = WM->getGlobalPosition(WM->getOppGoalieType());球门位置坐标为（52.5，0），可尝试朝（52.5，6.5）（52.5，-6.5）两点射门）

  ```
  
  else if (WM->isBallKickable())
  {
  	VecPosition vec = WM->getGlobalPosition(WM->getOppGoalieType());
  	if (vec.getY() > 0)
  	{
  		VecPosition pos = (52.2, -6.5);
  		soc = kickTo(pos, SS->getBallSpeedMax());
  	}
  	else
  	{
  		VecPosition pos1 = (52.5, 6.5);
  		soc = kickTo(pos1, SS->getBallSpeedMax());
  	}
  	ACT->putCommandInQueue(soc);
  	ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
  }
  
  ```

- 任务二：在 BasicPlay里填加一个带球函数，要求如果无人阻挡（带球将要经过的路线附近 没有对方球员）就朝球门方向带球，否则想办法避开对方球员带球前进（要求只要 作出闪避的动作即可，不要求效果）。 

  ① 打开 WorldModel.h ，在里面预定义函数，即写入`bool isOpponentAtAngleEx( AngDeg angA , AngDeg angB ,double dDist )` ；该函数用来判断当前球员角度在 angA~angB 之间距离小于 dDist 的范围内是否有对方队员。

  ② 找到并打开 WorldModel.c 在里面填加一个新函数

  ```
  
  bool WorldModel::isOpponentAtAngleEx(AngDeg angA, AngDeg angB, double dDist)
  {
  	VecPosition posAgent = getAgentGlobalPosition();
  	VecPosition posOpp;
  	AngDeg angOpp;
  	Int iIndex;
  	for (ObjectT o = iterateObjectStart(iIndex, OBJECT_SET_OPPONENTS);
  
  		 o != OBJECT_ILLEGAL;
  		 o = iterateObjectNext(iIndex, OBJECT_SET_OPPONENTS))
  	{
  		posOpp = getGlobalPosition(o);
  		angOpp = (posOpp - posAgent).getDirection();
  		if (angA <= angOpp && angOpp <= angB && posAgent.getDistanceTo(posOpp) < dDist)
  			return true;
  	}
  	iterateObjectDone(iIndex);
  	return false;
  }
  
  ```

  在 playerTeams.cpp中添加

  ```
  
  else if (WM->isBallKickable())
  {
  	Circle cir(posAgent, 2.5);
  	int num = WM->getNrInSetInCircle(OBJECT_SET_OPPONENTS, cir);
  	if (num < 2)
  	{
  		double ang = (VecPosition(52.5, 0) - posAgent).getDirection();
  		if (WM->isOpponentAtAngleEx(ang - 45, ang, 6))
  			ang += 45;
  		else if (WM->isOpponentAtAngleEx(ang, ang + 45, 6))
  			ang -= 45;
  		SoccerCommand soc = dribble(ang, DRIBBLE_SLOW);
  	}
  	else
  	{
  		soc = dribble(0.0, DRIBBLE_FAST);
  	}
  	ACT->putCommandInQueue(soc);
  	ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
  }
  
  ```

- 任务三：尝试修改视觉函数使得球员能更多的获得场上信息（要求不影响球员的动作）。
  在 Basicplayer.h 函数中声明：

  ```
  
  SoccerCommand BasicPlayer::view1(SoccerCommand soc)
  {
  	VecPosition positionAgent = WM->getAgentGlobalPosition();
  	AngDeg angdegBody = WM->getAgentGlobalBodyAngle();
  	AngDeg angdegTurn = 30;
  	switch (WM->getCurrentCycle() % 7)
  	{
  	case 0:
  		angdegTurn -= 60;
  	case 1:
  		ACT->putCommandInQueue(SoccerCommand(CMD_CHANGEVIEW, VA_NARROW, VQ_HIGH));
  		ACT->putCommandInQueue(turnNeckToPoint(positionAgent + VecPosition(5, VecPosition::normalizeAngle(angdegBody + angdegTurn), POLAR), soc));
  		break;
  	case 2:
  	case 3:
  		ACT->putCommandInQueue(SoccerCommand(CMD_CHANGEVIEW, VA_NORMAL, VQ_HIGH));
  		ACT->putCommandInQueue(turnNeckToPoint(positionAgent + VecPosition(5, angdegBody, POLAR), soc));
  		break;
  	case 4:
  	case 5:
  	case 6:
  		ACT->putCommandInQueue(SoccerCommand(CMD_CHANGEVIEW, VA_WIDE, VQ_HIGH));
  		break;
  	default:;
  	}
  }
  
  ```

  在 playerTeams.cpp 球可踢的条件下增加`ACT->putCommandInQueue(view1(soc));`即可获得更多的场上信息。

### 实验五 特殊比赛模式的开球设计

**1.实验目的**

（1）掌握 Robocup 仿真机器人足球比赛中特殊比赛模式发生的条件；

（2） 掌握 Robocup 仿真机器人足球比赛特殊比赛模式的规则要求；

（3） 了解 Robocup 仿真机器人足球比赛特殊比赛模式的战术设计思想；

进一步熟悉 WorldModel 类。 

**2、实验设备**

硬件环境：PC机

软件环境：操作系统Linux

**3. 实验内容及步骤**

（1） **角球。最近的球员开球，次近的球员跑到接应点。**

（2） **界外球。实验基本思路和内容和角球相同。编写程序，类似角球实现接应。**

（3）**定位球/任意球，设计思路和实验内容也类似角球。区别在于情况合适时可以选择直接射门。**

1. 角球是要求向场内踢。编写pointKickTo()返回在不同角时应该踢向的位置。

   当球在自己半场时，将位置的X坐标调大，尽量向对方半场踢；而在对方半场时，X设置得比较小，为夺球攻门创造机会。

   ```cpp
   
   // 在basicplayer.cpp里添加：
   VecPosition BasicPlayer::pointKickTo() // 计算角球应该踢向的点
   {
   	VecPosition posBall, posKickTo;
   	double x, y;
   	posBall = WM->getBallPos();
   	x = posBall.getX();
   	y = posBall.getY();
   	posKickTo.setX(-x / fabs(x) * 5 + x);
   	posKickTo.setY(-y / fabs(y) * 12 + y);
   	return posKickTo;
   }
   
   // 在PlayTeams.cpp里添加：
   else if (WM->isCornerKickUs()) // 我方角球
   {
   	if (WM->isBallKickable())
   	{
   		soc = kickTo(WM->pointKickTo(), 2.0);
   	}
   	else if (WM->getFastestInSetTo(OBJECT_SET_TEAMMATES, OBJECT_BALL, &iTmp) == WM->getAgentObjectType())
   	{
   		soc = moveToPos(posBall, PS->getPlayerWhenToTurnAngle());
   	}
   	else if (WM->getSecondClosestInSetTo(OBJECT_SET_TEAMMATES, OBJECT_BALL) == WM->getAgentObjectType())
   	{
   		soc = moveToPos(pointKickTo(), PS->getPlayerWhenToTurnAngle());
   	}
   	else
   	{
   		soc = moveToPos(WM->getStrategicPosition(), PS->getPlayerWhenToTurnAngle());
   	}
   
   	ACT->putCommandInQueue(soc);
   	ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
   }
   
   ```

   

2. 界外球和角球类似，区别在于比赛中很少有机会在对方底线发界外球。所以大部分情况都将接应点设置得更加靠近敌方半场，增加进攻机会。

   ```cpp
   
   // 在PlayTeams.cpp里添加：
   else if (WM->isKickInUs()) // 我方界外球
   {
   	if (WM->isBallKickable())
   	{
   		soc = kickTo(pointKickToK(), 2.0);
   	}
   	else if (WM->getFastestInSetTo(OBJECT_SET_TEAMMATES, OBJECT_BALL, &iTmp) == WM->getAgentObjectType())
   	{
   		soc = moveToPos(posBall, PS->getPlayerWhenToTurnAngle());
   	}
   	else if (WM->getSecondClosestInSetTo(OBJECT_SET_TEAMMATES, OBJECT_BALL) == WM->getAgentObjectType())
   	{
   		soc = moveToPos(pointKickToK(), PS->getPlayerWhenToTurnAngle());
   	}
   	else
   	{
   		soc = moveToPos(WM->getStrategicPosition(), PS->getPlayerWhenToTurnAngle());
   	}
   
   	ACT->putCommandInQueue(soc); // 放入命令队列
   	ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
   }
   // 在Basicplayer.cpp里添加：
   // 此函数返回界外球应该踢向的点，目的是把球尽可能往敌方半场踢
   VecPosition BasicPlayer::pointKickToK() // 计算界外球应该踢向的点
   {
   	VecPosition posBall, posKickTo;
   	double x, y;
   	posBall = WM->getBallPos();
   	x = posBall.getX();
   	y = posBall.getY();
   	posKickTo.setX(x + 12);
   	posKickTo.setY(-y / fabs(y) * 12 + y);
   	return posKickTo;
   }
   
   ```

   然后编译运行程序，观察球员的行为我们会发现当球可踢时，球员不再朝着球门的方向踢了，而是将球绕自己身体转动（UVA的这个底层动作经常把球转丢!）

3. 基本思路同界外球，都是尽可能向对方半场踢。但当条件合适（比如X比较大或者在禁区内），我们选择向较大的夹角直接射门。

   ```cpp
   
   else if (WM->isFreeKickUs()) // 我方任意球
   {
   	if (WM->isBallKickable())
   	{
   		if (WM->isInTheirPenaltyArea()) // 在禁区内直接射门
   		{
   			soc = maxAngShoot(posAgent);
   		}
   		else
   		{
   			soc = kickTo(pointKickToK(), 2.0);
   		}
   	}
   	else if (WM->getFastestInSetTo(OBJECT_SET_TEAMMATES, OBJECT_BALL, &iTmp) == WM->getAgentObjectType())
   	{
   		soc = moveToPos(posBall, PS->getPlayerWhenToTurnAngle());
   	}
   	else if (WM->getSecondClosestInSetTo(OBJECT_SET_TEAMMATES, OBJECT_BALL) == WM->getAgentObjectType())
   	{
   		soc = moveToPos(pointKickToK(), PS->getPlayerWhenToTurnAngle());
   	}
   	else
   	{
   		soc = moveToPos(WM->getStrategicPosition(), PS->getPlayerWhenToTurnAngle());
   	}
   
   	ACT->putCommandInQueue(soc); // 放入命令队列
   	ACT->putCommandInQueue(turnNeckToObject(OBJECT_BALL, soc));
   }
   
   ```

   







