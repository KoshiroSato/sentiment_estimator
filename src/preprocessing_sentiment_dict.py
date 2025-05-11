import pandas as pd

label_df = pd.read_excel('data/D18-2018.7.24.xlsx', sheet_name='感情分類')
data_df = pd.read_excel('data/D18-2018.7.24.xlsx', sheet_name='作業者A')

positive = [
    '安らぎ', '楽しさ', '親しみ', '尊敬・尊さ', '感謝', '気持ちが良い', '誇らしい', 
    '感動', '喜び', '好き', '穏やか', '祝う気持ち', '幸福感', '驚き', '興奮', '願望', '謝罪'
    ]
negative = [
    '悲しさ', '寂しさ', '不満', '切なさ', '苦しさ', '不安', '憂鬱', '辛さ', '不快', '失望', 
    '嫌悪', '恥ずかしい', '焦り', '怒り', '恨み', '恐れ（恐縮等の意味で）', '恐怖', '悔しさ', 
    '困惑', 'きまずさ', '悩み', 'あわれみ', '見下し', 'ためらい', '怠さ', 'あきれ', '心配', 
    '緊張', '妬み', '憎い', '残念', '情けない'
    ]

positive_df = label_df[label_df['Emotion'].isin(positive)]
negative_df = label_df[label_df['Emotion'].isin(negative)]

def relabeling(text):
    '''
    辞書に付けられたラベルがマルチラベルのため、ラベル1つ1つにpositiveグループは+1、negativeグループは-1でスコアリングし、
    総和の正負でそのデータがpositiveかnegativeか2値に判定する
    '''
    score = 0
    for char in list(text):
        if char in positive_df['Symbol(全て全角)'].tolist():
            score += 1
        elif char in negative_df['Symbol(全て全角)'].tolist():
            score -= 1
    if score >= 0:
        return 1
    return -1

data_df['label'] = data_df['Emotion'].map(relabeling)

data_df[['Word', 'label']].to_csv('data/emotional_expression_dict.csv', header=False, index=False)