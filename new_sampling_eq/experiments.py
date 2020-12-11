import numpy as np
from decimal import Decimal


alfa1 = Decimal('2.502792534335692477674277649')
alfa2 = Decimal('2.502929173074250806859646146')
alfa3 = Decimal('2.502973283048104508152318373')

alfa_new = alfa3 - (alfa2-alfa1)**2/(alfa3 - 2*alfa2 + alfa1)

print(alfa_new)
