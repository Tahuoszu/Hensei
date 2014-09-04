function [segmentSeries tmpOn durations] = tsMultiLevelSegment(tmpSeries, nbSegments)
% Perform piecewise linear approximation on the series
segments = bottomUpSegmentation(tmpSeries, nbSegments);
% Compute entropy for each base segment
for i = 1:length(segments)
    segVal = tmpSeries(segments(i).lx:segments(i).rx);
    segments(i).entropy = approximateEntropy(1, 0.2 * std(tmpSeries), segVal);
    segments(i).deltaEnt = inf;
end
tmpQueue = segments;
hierarchicalSegment = segments;
curSegment = segments(1);
while ~(curSegment.lx == 1 && curSegment.rx == length(tmpSeries))
    deltaEntropy = zeros(length(tmpQueue) - 1, 1);
    for i = 1:(length(tmpQueue) - 1)
        if isinf(tmpQueue(i).deltaEnt)
            segVal = tmpSeries(tmpQueue(i).lx:tmpQueue(i + 1).rx);
            tmpEntropy = approximateEntropy(1, 0.2 * std(tmpSeries), segVal);
            tmpQueue(i).deltaEnt = tmpEntropy - (tmpQueue(i).entropy + tmpQueue(i + 1).entropy);
        end
        deltaEntropy(i) = tmpQueue(i).deltaEnt;
    end
    [v eID] = max(deltaEntropy);
    curSegment = struct;
    curSegment.lx = tmpQueue(eID).lx;
    curSegment.ly = tmpQueue(eID).ly;
    curSegment.rx = tmpQueue(eID + 1).rx;
    curSegment.ry = tmpQueue(eID + 1).ry;
    curSegment.mc = 0;
    curSegment.best = [];
    segVal = tmpSeries(tmpQueue(eID).lx:tmpQueue(eID + 1).rx);
    curSegment.entropy = approximateEntropy(2, 0.2 * std(tmpSeries), segVal);
    curSegment.deltaEnt = inf;
    hierarchicalSegment = [curSegment hierarchicalSegment];
    newQueue = [];
    if (eID > 1)
        newQueue = tmpQueue(1:(eID - 1));
    end
    newQueue = [newQueue curSegment];
    if (eID < length(tmpQueue) - 1)
        newQueue = [newQueue tmpQueue((eID + 2):end)];
    end
    tmpQueue = newQueue;
end
% figure;
% plot(tmpSeries ./ std(tmpSeries));
% hold on;
segmentSeries = cell(length(hierarchicalSegment) - 1, 1);
tmpOn = zeros(length(hierarchicalSegment) - 1, 1);
durations = zeros(length(hierarchicalSegment) - 1, 1);
for i = 2:length(hierarchicalSegment)
    curSegment = hierarchicalSegment(i);
    segmentSeries{i - 1} = tmpSeries(curSegment.lx:curSegment.rx);
    tmpOn(i - 1) = curSegment.lx;
    durations(i - 1) = curSegment.rx - curSegment.lx + 1;
%      tmpY = (length(hierarchicalSegment) - i) ./ length(hierarchicalSegment);
%        if (i < (length(hierarchicalSegment) - length(segments) + 1))
%            line([hierarchicalSegment(i).lx hierarchicalSegment(i).rx], [tmpY tmpY], 'Color', 'r', 'LineWidth', 4);
%        else
%            line([hierarchicalSegment(i).lx hierarchicalSegment(i).rx], [(0.5 + mod(i,2) / 2) (0.5 + mod(i,2) / 2)], 'Color', 'g', 'LineWidth', 2);
%        end
end
%hold off;