"""
Filename: main.py
Author: 郑鑫业 2023217265 计算机23-1
Note: This script is used to build and visualize a decision tree using the ID3 algorithm.
"""

# 导入numpy和我们自己写的TreePlotter
import numpy as np
import TreePlotter
# 数据集
data = np.array([
    [1, 1, 2, 2, 2, 0, 1],
    [1, 1, 0, 3, 1, 2, 0],
    [0, 0, 0, 0, 2, 0, 1],
    [1, 1, 0, 3, 1, 1, 1],
    [1, 0, 2, 2, 1, 3, 0],
    [0, 1, 1, 1, 2, 0, 1],
    [0, 0, 0, 0, 0, 0, 0],
    [0, 1, 1, 3, 2, 0, 1],
    [0, 0, 0, 0, 1, 3, 0],
    [1, 1, 2, 1, 1, 1, 0],
    [1, 0, 0, 3, 0, 0, 0],
    [0, 1, 0, 0, 1, 2, 1]
])

def GetEntropy(data):
    # 计算数据集的熵
    labels = data[:, -1]
    UniqueLabels, LabelCounts = np.unique(labels, return_counts=True)
    entropy = 0
    TotalSamples = len(labels)
    for count in LabelCounts:
        p = count / TotalSamples
        entropy -= p * np.log2(p)
    return entropy

def GetInformationGain(data, FeatureIndex):
    # 计算信息增益
    UniqueValues, ValueCounts = np.unique(data[:, FeatureIndex], return_counts=True)
    TotalSamples = len(data)
    gain = GetEntropy(data)
    for value, count in zip(UniqueValues, ValueCounts):
        subset = data[data[:, FeatureIndex] == value]
        gain -= (count / TotalSamples) * GetEntropy(subset)
    return gain

def BuildId3Tree(data, features):
    UniqueLabels = np.unique(data[:, -1])

    # 如果所有样本都属于同一类别，返回叶子节点
    if len(UniqueLabels) == 1:
        return UniqueLabels[0]

    # 如果没有更多特征可用，返回数据集中最常见的类别
    if len(features) == 0:
        LabelCounts = np.bincount(data[:, -1].astype(int))
        return np.argmax(LabelCounts)

    # 选择信息增益最大的特征
    BestFeature = None
    BestGain = -1

    for FeatureIndex in features:
        Gain = GetInformationGain(data, FeatureIndex)
        if Gain > BestGain:
            BestGain = Gain
            BestFeature = FeatureIndex

    # 如果最佳信息增益为0，返回数据集中最常见的类别
    if BestGain == 0:
        LabelCounts = np.bincount(data[:, -1].astype(int))
        return np.argmax(LabelCounts)

    # 创建根节点
    Tree = {BestFeature: {}}
    UniqueValues = np.unique(data[:, BestFeature])

    NewFeatures = [f for f in features if f != BestFeature]

    # 递归构建子树
    for value in UniqueValues:
        subset = data[data[:, BestFeature] == value]
        Tree[BestFeature][value] = BuildId3Tree(subset, NewFeatures)

    return Tree

# 获取特征列索引
features = list(range(data.shape[1] - 1))

# 构建决策树
DecisionTree = BuildId3Tree(data, features)

# 打印决策树
TreePlotter.createPlot(DecisionTree)
print(DecisionTree)