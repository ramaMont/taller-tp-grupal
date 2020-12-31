
-- local bot = {
--     mapa = {},
--     mapa_size = {ancho = 0, alto = 0},
--     grafo = {},
--     enemigos = {},
--     enemigo_actual = false,
--     abriPuerta = false
-- }

-- -- Eventos
-- local ADELANTE = 0
-- local IZQUIERDA = 1
-- local DERECHA = 2
-- local DISPARAR = 3
-- local CAMBIAR_ARMA_CUCHILLO = 4
-- local ABRIR_PUERTA = 5


-- -- Mapa
-- local VACIO  = 0
-- local OCUPADO = 1
-- local PUERTA = 2
-- local ENEMIGO = 3


-- local PI = 3.1415926535898
-- local MOVIMIENTOS = 50


-- -- Funciones Locales

-- function bot.crearVertices()
-- 	for i = 1, bot.mapa_size.ancho do 
-- 	    bot.grafo[i] = {}
-- 		for j = 1, bot.mapa_size.alto do
-- 		    if (bot.mapa[i][j] ~= OCUPADO) then
-- 				bot.grafo[i][j] = {x = i, y = j, aristas = {}}
--             end
-- 		end
-- 	end
-- end

-- function bot.agregarArista(v_x, v_y, x, y)
--     if (1 <= x and x <= bot.mapa_size.ancho and
--         1 <= y and y <= bot.mapa_size.alto and bot.mapa[x][y] ~= OCUPADO) then
--         table.insert(bot.grafo[v_x][v_y].aristas, bot.grafo[x][y])
--     end
-- end

-- function bot.crearAristas()
-- 	for i = 1, bot.mapa_size.ancho do 
-- 		for j = 1, bot.mapa_size.alto do
-- 		    if (bot.mapa[i][j] ~= OCUPADO) then
-- 				bot.agregarArista(i, j, i-1, j)
-- 				bot.agregarArista(i, j, i+1, j)
-- 				bot.agregarArista(i, j, i, j-1)
-- 				bot.agregarArista(i, j, i, j+1)
-- 				bot.agregarArista(i, j, i-1, j-1)
-- 				bot.agregarArista(i, j, i-1, j+1)
-- 				bot.agregarArista(i, j, i+1, j-1)
-- 				bot.agregarArista(i, j, i+1, j+1)
-- 			end
-- 		end
-- 	end
-- end

-- function bot.crearGrafo()
--     bot.crearVertices()
--     bot.crearAristas()
-- end

-- function bot.visitarAristas(visitados, cola)
--     inicio = 1
-- 	while inicio ~= #cola+1 do
-- 	    x, y = cola[inicio][1], cola[inicio][2]
-- 	    inicio = inicio + 1
	    
-- 	    if bot.mapa[x][y] == ENEMIGO then
-- 	        return x, y, visitados
-- 	    end

-- 	    for j = 1, #bot.grafo[x][y].aristas do
-- 	        arista = bot.grafo[x][y].aristas[j]
-- 	        if (not visitados[arista.x][arista.y].v) then
-- 	            visitados[arista.x][arista.y] = {v = true, anterior = {x,y}}
-- 	            cola[#cola+1] = {arista.x, arista.y}
-- 	        end
-- 	    end
-- 	end
-- 	return false, false, false
-- end

-- function bot.bfs(inicio_x, inicio_y)
--     cola = {}
--     visitados = {}
--  	for i = 1, bot.mapa_size.ancho do 
--  	    visitados[i] = {}
-- 		for j = 1, bot.mapa_size.alto do
-- 		    visitados[i][j] = {v = false, anterior = 0}
-- 		end
-- 	end
-- 	visitados[inicio_x][inicio_y] = {v = true, anterior = {0,0}}
-- 	cola[1] = {inicio_x, inicio_y}
-- 	return bot.visitarAristas(visitados, cola)
-- end


-- -- Decide si tiene que abrir una puerta
-- function bot.abrePuerta(pos_x, pos_y, dir_x, dir_y)
--     if bot.mapa[pos_x+dir_x][pos_y+dir_y] == PUERTA and not bot.abriPuerta then
--         bot.abriPuerta = true
-- 	    return true
-- 	end
-- 	return false
-- end


-- function bot.tengoEnemigoAdelante(pos_x, pos_y, dir_x, dir_y)
--     return bot.mapa[pos_x+dir_x][pos_y+dir_y] == ENEMIGO 
-- end


-- function bot.tengoEnemigoAlrededor(pos_x, pos_y)
--     for i = 1, #bot.grafo[pos_x][pos_y].aristas do
-- 	    arista = bot.grafo[pos_x][pos_y].aristas[i]
--         if bot.mapa[arista.x][arista.y] == ENEMIGO then
-- 	        return true, arista.x, arista.y
-- 	    end
-- 	end
-- 	return false, 0, 0
-- end

-- -- Decide la direccion del movimiento
-- function bot.calcularMovimiento(pos_x, pos_y, dir_x, dir_y, ene_x, ene_y)
--     ene_x = ene_x - pos_x
--     ene_y = ene_y - pos_y
--     angulo = math.atan2(ene_y, ene_x) - math.atan2(dir_y, dir_x)

--     if angulo > PI or angulo < -PI then
--         angulo = -angulo
--     end
    
--     if angulo == 0 then
--         return ADELANTE
--     elseif angulo < 0 then
--         return DERECHA
--     end
--     return IZQUIERDA
-- end

-- -- Busca al enemigo mas cercano y guarda el camino
-- function bot.encontrarEnemigo(pos_x, pos_y)
--     x, y, visitados = bot.bfs(pos_x, pos_y)
--     if not visitados then
--         return false
--     end
--     bot.enemigo_actual = {pasos = {}, actual = 1, movimientos = MOVIMIENTOS}
--     anterior = visitados[x][y].anterior
--     while anterior[1] ~= pos_x or anterior[2] ~= pos_y do
--         x, y = anterior[1], anterior[2]
--         table.insert(bot.enemigo_actual.pasos, {x,y})
--         anterior = visitados[x][y].anterior
--     end
--     return true
-- end

-- -- Decide para donde moverse en base al camino hacia su enemigo
-- function bot.generarMovimiento(pos_x, pos_y, dir_x, dir_y)
--     posicion_siguiente = bot.enemigo_actual.pasos[bot.enemigo_actual.actual]
--     if pos_x == posicion_siguiente[1] and pos_y == posicion_siguiente[2] then
--         bot.enemigo_actual.actual = bot.enemigo_actual.actual + 1
--         posicion_siguiente = bot.enemigo_actual.pasos[bot.enemigo_actual.actual]
--     end
--     x = posicion_siguiente[1]
--     y = posicion_siguiente[2]

--     bot.enemigo_actual.movimientos = bot.enemigo_actual.movimientos - 1
--     if bot.enemigo_actual.movimientos == 0 then
--         bot.enemigo_actual = false
--     end
--     return bot.calcularMovimiento(pos_x, pos_y, dir_x, dir_y, x, y)
-- end

-- -- Agrega las posiciones de los enemigos en el mapa
-- function bot.agregarEnemigosAlMapa(...)
-- 	local arg = {...}
--     for i = 1, #arg/2 do
-- 		bot.enemigos[i] = {x = math.floor(arg[i+i-1]) + 1,
-- 		                   y = math.floor(arg[i*2]) + 1}
--         bot.mapa[bot.enemigos[i].x][bot.enemigos[i].y] = ENEMIGO
--     end 
-- end

-- -- Borra las posiciones de los enemigos del mapa
-- function bot.borrarEnemigosAnterioresDelMapa()
--     for i = 1, #bot.enemigos do
--         bot.mapa[bot.enemigos[i].x][bot.enemigos[i].y] = VACIO
--     end
--     bot.enemigos = {}
-- end


-- -- Funciones publicas

-- function bot.cargarMapa(objeto, ancho, alto)
--     bot.mapa_size.ancho = ancho
--     bot.mapa_size.alto = alto
-- 	for x = 1, ancho do 
-- 	    bot.mapa[x] = {}
-- 		for y = 1, alto do
-- 			bot.mapa[x][y]  = obtenerObjetoMapa(objeto, x - 1, y - 1)
-- 		end
-- 	end
-- 	bot.crearGrafo()
-- end

-- function bot.generarEvento(n_arma, pos_x, pos_y, dir_x, dir_y, ...)
--     if n_arma ~= 0 then
-- 	    return CAMBIAR_ARMA_CUCHILLO
-- 	end
	
--     pos_x = math.floor(pos_x) + 1
--     pos_y = math.floor(pos_y) + 1
--     dir_x = math.ceil(dir_x - 0.5)
--     dir_y = math.ceil(dir_y - 0.5)
    
--     if bot.mapa[pos_x][pos_y] == PUERTA then
--         bot.abriPuerta = false
--         return ADELANTE
--     end
--     if bot.abrePuerta(pos_x, pos_y, dir_x, dir_y) then
--         return ABRIR_PUERTA
--     end
    
--     bot.borrarEnemigosAnterioresDelMapa();
--     bot.agregarEnemigosAlMapa(...)
       
--     if bot.tengoEnemigoAdelante(pos_x, pos_y, dir_x, dir_y) then
--         return DISPARAR
--     end
    
--     res, x, y = bot.tengoEnemigoAlrededor(pos_x, pos_y)
--     if res then
--         return bot.calcularMovimiento(pos_x, pos_y, dir_x, dir_y, x, y)
--     end     

--     if not bot.enemigo_actual then 
--         if not bot.encontrarEnemigo(pos_x, pos_y) then 
--             return ADELANTE
--         end
--     end
--     return bot.generarMovimiento(pos_x, pos_y, dir_x, dir_y)
-- end


-- return bot

